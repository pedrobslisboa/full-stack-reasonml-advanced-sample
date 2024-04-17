project_name = fullstack-reason-react

DUNE = opam exec -- dune
opam_file = $(project_name).opam

.PHONY: help
help:
	@echo "";
	@echo "List of available make commands";
	@echo "";
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "  \033[36m%-15s\033[0m %s\n", $$1, $$2}';
	@echo "";

.PHONY: build
build:
	$(DUNE) build @all

.PHONY: build-dev
dev:
	$(DUNE) build -w @all

.PHONY: build-prod
build-prod:
	$(DUNE) build --profile=prod @all

.PHONY: clean
clean:
	$(DUNE) clean

.PHONY: format
format: 
	$(DUNE) build @fmt --auto-promote

.PHONY: analize
analize: build
	yarn webpack --env production --env analize

.PHONY: format-check
format-check:
	$(DUNE) build @fmt

.PHONY: create-switch
create-switch:
	opam switch create . 5.1.1 --deps-only --with-test -y

.PHONY: install
install: create-switch

.PHONY: docker-build
docker-build:
	docker build -t fullstack-reason-react .

.PHONY: docker-run
docker-run:
	docker run -p 8080:8080 fullstack-reason-react

.PHONY: run
run: build
	yarn webpack
	_build/default/src/server/server.exe

.PHONY: run-prod
run-prod: build-prod
	yarn webpack --env production
	_build/default/src/server/server.exe

.PHONY: server
server: build
	$(DUNE) exec src/server/server.exe