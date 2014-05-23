
MAKE = emake

subdirs := bhd btosps copysps fea2esig fea_deriv feafunc get_esps_base \
           getparam hditem mergefea misc nodiff pplain psps stats testsd \
           tofeasd

.PHONY: all $(subdirs)

all: $(subdirs)

$(subdirs):
	$(MAKE) -C $@
