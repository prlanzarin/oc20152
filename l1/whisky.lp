Maximize
	lucro:	68xa+57xb+45xc-70xj-50xo-40xm
Subject to
	limiteJohnny:	xj<=2000
	limiteOldGarg:	xo<=2500
	limiteMisty:	xm<=1200

	percJohnnyA:	xja-0.6xa>=0
	percMistzA:	xma-0.2xa<=0
	percJohnnyB:	xjb-0.15xb>=0
	percMistyB:	xmb-0.6xb<=0
	percMistyC:	xmc-0.5xc<=0

	totalJohnny:	xj-xja-xjb-xjc=0
	totalOldGarg:	xo-xoa-xob-xoc=0
	totalMisty:	xm-xma-xmb-xmc=0
	totalA:		xa-xja-xoa-xma=0
	totalB:		xb-xjb-xob-xmb=0
	totalC:		xc-xjc-xoc-xmc=0
Bounds
	0 <= xja
	0 <= xjb
	0 <= xjc
	0 <= xma
	0 <= xmb
	0 <= xmc
	0 <= xoa
	0 <= xob
	0 <= xoc
End
