# 
# Written by:  Ronald L. Sprouse (ronald@berkeley.edu)
# Checked by:
# Revised by:
# 
# Brief description: makefile for esps_speech
# 

MAKE = emake

subdirs := acf addsd cb_filt cbkd cbkedit cepanal classify dtw ebanner epochs \
           fft filter2 filtspec find_ep get_f0 formant get_resid iir_filt \
           lpcana melspec notch_filt pkmc_filt refcof rem_dc rformant \
           sgram spectrans transpec vq vqclassify vqdst win_filt \
           wmse_filt zcross zero_pad

isubdirs := acf addsd cb_filt cbkd cbkedit cepanal classify dtw ebanner epochs \
           fft filter2 filtspec find_ep get_f0 formant get_resid iir_filt \
           lpcana melspec notch_filt pkmc_filt refcof rem_dc rformant \
           sgram spectrans transpec vq vqclassify vqdst win_filt \
           wmse_filt zcross zero_pad

.PHONY: all $(subdirs)

all: $(subdirs)

$(subdirs):
	$(MAKE) -C $@

.PHONY: install $(isubdirs)

install: $(isubdirs)

$(isubdirs):
	$(MAKE) -C $@ install
