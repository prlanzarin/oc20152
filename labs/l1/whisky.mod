# conjuntos basicos de indices
set misturas;
set marcas  ;

# custo de cada garafa por marca
param custoMarca { marcas } >= 0;
# preco de cada mistura
param precoMistura { misturas } >= 0;
# limite de importacao de cada marca
param limiteMarca { marcas } >= 0;
# percentagens minimas das marcas nas misturas
param percMin { marcas, misturas } >= 0, <= 1, default 0;
# percentages maximas das marcas nas misturas
param percMax { marcas, misturas } >= 0, <= 1, default 1;

# numero de garrafas
var numMistura { misturas } >= 0;
var numMarca   { marcas } >= 0;
var numGarrafas { marcas, misturas } >= 0;

# definicao do modelo

maximize lucro:
	sum { j in misturas } precoMistura[j]*numMistura[j] -
	sum { j in marcas } custoMarca[j]*numMarca[j];

subject to limitesImportacao { m in marcas }:
	numMarca[m] <= limiteMarca[m];
subject to maxPercentagens { m in marcas, i in misturas }:
	numGarrafas[m,i] <= percMax[m,i]*numMistura[i];
subject to minPercentagens { m in marcas, i in misturas }:
	numGarrafas[m,i] >= percMin[m,i]*numMistura[i];
subject to totalMarca { m in marcas }:
	numMarca[m] = sum { j in misturas } numGarrafas[m,j];
subject to totalMistura { m in misturas }:
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
