.PHONY:all
all:client select

client:client.c
	gcc -o $@ $^
select:select.c
	gcc -o $@ $^

.PHONY:clean
clean:
	rm -f client select
