#include <string>
#include <queue>
#include <unordered_set>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <atomic>
#include <filesystem>
#include <iostream>
#include <stdexcept>

// Forward declarations of provided functions
using URL = std::string;
using HTML = std::string;

HTML fetch(const URL& url);
std::vector<URL> parse(const HTML& html);
void save(const URL& url, const HTML& content);

class WebCrawler {
private:
	struct CrawlTask {
		URL url;
		int depth;
		
		CrawlTask(URL u, int d) : url(std::move(u)), depth(d) {}
	};

	// Thread-safe queue for crawl tasks
	class TaskQueue {
	private:
		std::queue<CrawlTask> tasks_;
		std::mutex mutex_;
		std::condition_variable cv_;
		bool shutdown_{false};

	public:
		void push(CrawlTask task) {
			std::lock_guard<std::mutex> lock(mutex_);
			tasks_.push(std::move(task));
			cv_.notify_one();
		}

		bool pop(CrawlTask& task) {
			std::unique_lock<std::mutex> lock(mutex_);
			cv_.wait(lock, [this] { return !tasks_.empty() || shutdown_; });
			
			if (shutdown_ && tasks_.empty()) {
				return false;
			}

			task = std::move(tasks_.front());
			tasks_.pop();
			return true;
		}

		void shutdown() {
			std::lock_guard<std::mutex> lock(mutex_);
			shutdown_ = true;
			cv_.notify_all();
		}
	};

	const int max_depth_;
	const size_t num_threads_;
	std::atomic<size_t> active_tasks_{0};
	
	// Thread-safe visited URL tracking
	std::unordered_set<URL> visited_;
	std::mutex visited_mutex_;

	TaskQueue task_queue_;
	std::vector<std::thread> workers_;

	bool hasVisited(const URL& url) {
		std::lock_guard<std::mutex> lock(visited_mutex_);
		return visited_.find(url) != visited_.end();
	}

	void markVisited(const URL& url) {
		std::lock_guard<std::mutex> lock(visited_mutex_);
		visited_.insert(url);
	}

	void processSingleURL(const CrawlTask& task) {
		try {
			// Skip if already visited
			if (hasVisited(task.url)) {
				return;
			}

			// Mark as visited before fetching to prevent race conditions
			markVisited(task.url);

			// Fetch and save content
			HTML content = fetch(task.url);
			save(task.url, content);

			// If we haven't reached max depth, parse and queue new URLs
			if (task.depth < max_depth_) {
				std::vector<URL> links = parse(content);
				for (const auto& link : links) {
					task_queue_.push(CrawlTask(link, task.depth + 1));
					active_tasks_++;
				}
			}
		} catch (const std::exception& e) {
			std::cerr << "Error processing URL " << task.url 
					  << ": " << e.what() << std::endl;
		}
		active_tasks_--;
	}

	void workerThread() {
		CrawlTask task(""s, 0);
		while (task_queue_.pop(task)) {
			processSingleURL(task);
		}
	}

public:
	WebCrawler(int max_depth, size_t num_threads = std::thread::hardware_concurrency())
		: max_depth_(max_depth)
		, num_threads_(num_threads == 0 ? 1 : num_threads) {}

	void crawl(const URL& start_url) {
		// Reset state
		visited_.clear();
		active_tasks_ = 1;  // Count the initial task

		// Initialize worker threads
		for (size_t i = 0; i < num_threads_; ++i) {
			workers_.emplace_back(&WebCrawler::workerThread, this);
		}

		// Queue initial task
		task_queue_.push(CrawlTask(start_url, 0));

		// Wait until all tasks are complete
		while (active_tasks_ > 0) {
			std::this_thread::yield();
		}

		// Shutdown and cleanup
		task_queue_.shutdown();
		for (auto& worker : workers_) {
			if (worker.joinable()) {
				worker.join();
			}
		}
		workers_.clear();
	}

	~WebCrawler() {
		task_queue_.shutdown();
		for (auto& worker : workers_) {
			if (worker.joinable()) {
				worker.join();
			}
		}
	}
};

// Example usage
int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " <start_url> <depth>\n";
		return 1;
	}

	try {
		int depth = std::stoi(argv[2]);
		if (depth < 0) {
			throw std::invalid_argument("Depth must be non-negative");
		}

		WebCrawler crawler(depth);
		crawler.crawl(argv[1]);
		return 0;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return 1;
	}
}
