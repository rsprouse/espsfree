
MAKE = emake
#fea2esig 
subdirs := bhd btosps copysps fea_deriv feafunc get_esps_base \
           getparam hditem mergefea misc nodiff pplain psps stats testsd \
           tofeasd

.PHONY: all $(subdirs)
all: $(subdirs)

.PHONY: $(subdirs)
$(subdirs):
	$(MAKE) -C $@

.PHONY: install
install: $(subdirs)
	for prog in $(subdirs); do \
		$(MAKE) -C $$prog install; \
	done

.PHONY: clean
clean:
	for prog in $(subdirs); do \
		$(MAKE) -C $$prog clean; \
	done


