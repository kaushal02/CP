FILE := a.cc
TEMPLATE := template2.cc
CODEDIR := Online-Judges

run: $(FILE)
	g++ -std=c++11 -fmax-errors=2 $(FILE)
	./a.out <a.in
	make clean

%: $(TEMPLATE) $(CODEDIR)/%
	cp $(TEMPLATE) $(CODEDIR)/$@/$(FILE)
	git add $(CODEDIR)/$@/$(FILE)
	@echo $(CODEDIR)/$@/$(FILE)

clean:
	rm -f a.out