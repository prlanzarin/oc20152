# conjuntos basicos de indices
set misturas;
set marcas  ;

# horas de estudo a b c
param ha { horas_a } >= 0, <= 100;
param hb { horas_b } >= 0, <= 100;
param hc { horas_c } >= 0, <= 100;

# 
var nfa  { nota_a } >= 5;
var nfb  { nota_b } >= 5;
var nfc  { nota_c } >= 5;
var numMarca   { marcas } >= 0;
var numGarrafas { marcas, misturas } >= 0;

# definicao do modelo

maximize lucro:
	sum { j in misturas } precoMistura[j]*numMistura[j] -
	sum { j in marcas } custoMarca[j]*numMarca[j];

subject to  :
	numMistura[m] = sum { j in marcas } numGarrafas[j,m];

# definicao dos dados
data;

# formato de tabela: a 1a coluna define o conjunto marcas
# e os seguintes colunas os valores de parametros que
# dependem de marcas
param : marcas : custoMarca  limiteMarca :=
	'J'	70		2000
	'O'	50		2500
	'M'	40		1200	;

# tabela para misturas
param : misturas : precoMistura :=
	'A'		68
	'B'		57
	'C'		45	;

# definicao de percMin em formato de matriz:
# a 1a linha contem os 1os indices da matriz
# a 1a coluna contem os 2os indices da matriz
# o valor "." significa usar o default
param percMin : 'A'  'B'    'C' :=
	'J'	0.6  0.15   .
	'O'	.    .      .
	'M'     .    .      .	;

# matrix das percentagens maximos
param percMax : 'A'  'B'  'C' :=
	'J'     .    .    .
	'O'     .    .    .
	'M'     0.20 0.60 0.50	;

end;
