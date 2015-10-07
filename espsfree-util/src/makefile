
MAKE = emake
#fea2esig 
subdirs := bhd btosps copysps fea_deriv feafunc get_esps_base \
           getparam hditem mergefea misc nodiff pplain psps stats testsd \
           tofeasd

isubdirs := bhd btosps copysps fea_deriv feafunc get_esps_base \
           getparam hditem mergefea misc nodiff pplain psps stats testsd \
           tofeasd wav2sd

.PHONY: all $(subdirs)

all: $(subdirs)

$(subdirs):
	$(MAKE) -C $@

.PHONY: install $(isubdirs)

install: $(isubdirs)

$(isubdirs):
	$(MAKE) -C $@ install
