# 
# Written by:  Ronald L. Sprouse (ronald@berkeley.edu)
# Checked by:
# Revised by:
# 
# Brief description: makefile for esps_speech
# 

MAKE = emake

subdirs := acf addsd cb_filt cbkd cbkedit cepanal classify dtw ebanner fft \
           filter2 filtspec find_ep formant get_f0 get_resid iir_filt \
           libsig lpcana melspec notch_filt pkmc_filt rem_dc \
           rformant sgram sigproc vq vqclassify vqdst win_filt \
           wmse_filt zcross zero_pad

.PHONY: all $(subdirs)

all: $(subdirs)

$(subdirs):
	$(MAKE) -C $@
