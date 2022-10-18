CXX ?= g++
CXXFLAGS ?= -std=c++14 # -fmax-errors=2
TEMPLATE ?= template2.cc
CODEDIR ?= Online-Judges

run:
ifdef FILE
	$(CXX) $(CXXFLAGS) $(FILE)
	./a.out <a.in
	$(MAKE) clean
else
	@echo "running a.cc"
	$(CXX) $(CXXFLAGS) a.cc
	./a.out <a.in
	$(MAKE) clean
endif

%: $(CODEDIR)/%
ifdef FILE
	cp $(TEMPLATE) $</$(FILE)
	git add $</$(FILE)
	@echo $</$(FILE)
else
	@echo "please provide FILE"
endif

clean:
	rm -f a.out
