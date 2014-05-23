# 
# Written by:  Ronald L. Sprouse (ronald@berkeley.edu)
# Checked by:
# Revised by:
# 
# Brief description: makefile for esps_speech
# 

MAKE = emake
#formant get_resid rformant
subdirs := acf addsd cb_filt cbkd cbkedit cepanal classify dtw ebanner fft \
           filter2 filtspec find_ep get_f0 iir_filt \
           libsig lpcana melspec notch_filt pkmc_filt rem_dc \
           sgram sigproc vq vqclassify vqdst win_filt \
           wmse_filt zcross zero_pad

.PHONY: all $(subdirs)

all: $(subdirs)

$(subdirs):
	$(MAKE) -C $@
