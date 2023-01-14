
CC = gcc

SOURCES:= $(wildcard *.c)
BINARIES:= $(patsubst %.c, %, $(SOURCES))

all: ${BINARIES}
	@mkdir ./bin/ 2>/dev/null || true
	@for i in ${BINARIES}; do \
		echo "moving binaries.."; \
		mv $$i ./bin; \
	done

%.o: %.c
	@echo "Creating object.."
	${CC} $<

clean:
	@echo "Cleaning up.."
	@cd ./bin && rm -f ${BINARIES}   1>/dev/null || true
	@rm -rf ./bin 1>/dev/null || true