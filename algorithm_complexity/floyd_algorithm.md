## Cálculo da complexidade do Algoritmo de Floyd Modificado

Autor: João Vicente Souto

Disciplina: INE5408 - Estrutura de Dados - UFSC

### Pseudocódigo:
```
FloydModificado()
início
	para i = 1 até n faça
		para j = 1 até n faça
			A[i,j] <- D[i,j];
			R[i,j] <- 0;
		fim para
	fim para

	para i = 1 até n faça
		A[i,i] <- 0;
	fim para

	para k = 1 até n faça
		para i = 1 até n faça
			para j = 1 até n faça
				se A[i,k] + A[k,j] < A[i,j] então
					A[i,j] <- A[i,k] + A[k,j];
					R[i,j] <- k;
			fim para
		fim para
	fim para
fim
```

## Análise:

#### Considerações:
- __Cálculo será dividido nos 3 laços independentes do algoritmo e somados no final.__
- Cada operação de atribuição, aritmética e comparação consomem uma unidade.
- Laços executam x vezes o que possuem dentro, x em função do laço.
- Funções normais (sem considerar as recursivas) custam as unidades de suas operações internas.
- _Cálculo é efetuado de dentro para fora em laços e funções._

### Primeiro laço principal
```
para i = 1 até n faça
	para j = 1 até n faça
		A[i,j] <- D[i,j];
		R[i,j] <- 0;
	fim para
fim para
```
Dentro do laço interno:
- 2 atribuições;
- *Executado n vezes*

Laço interno:
- 1 atribuição de j;
- n+1 comparações de j e n;
- n incrementos de j;
- *Executado n vezes.*

Laço principal:
- 1 atribuição de i;
- n+1 comparações de i e n;
- n incrementos de i.

1º Cálculo: `n*(n*2 + n+(n+1)+1) + n+(n+1)+1` = `4n^2 + 4n + 2`

### Segundo laço principal
```
para i = 1 até n faça
	A[i,i] <- 0;
fim para
```
Dentro do laço:
- 1 atribuições;
- *Executado n vezes.*

Laço:
- 1 atribuição de i;
- n+1 comparações de i e n;
- n incrementos de i.

2º Cálculo = `n*1 + n+(n+1)+1` = `3n + 2`

### Terceiro laço principal
```
para k = 1 até n faça
	para i = 1 até n faça
		para j = 1 até n faça
			se A[i,k] + A[k,j] < A[i,j] então
				A[i,j] <- A[i,k] + A[k,j];
				R[i,j] <- k;
		fim para
	fim para
fim para
```
Dentro do laço interno:
- 2 atribuições;
- 2 somas;
- 1 comparação;
- *Executado n vezes;*
- *Considerando o pior caso em que (A[i,k] + A[k,j] < A[i,j]) sempre seja verdadeiro.*

Laço interno:
- 1 atribuição de j;
- n+1 comparações de j e n;
- n incrementos de j;
- *Executado n vezes.*

Laço intermediário:
- 1 atribuição de i;
- n+1 comparações de i e n;
- n incrementos de i;
- *Executado n vezes.*

Laço principal:
- 1 atribuição de k;
- n+1 comparações de k e n;
- n incrementos de k;

3º Cálculo = `n*(n*(n*5 + n+(n+1)+1) + n+(n+1)+1) + n+(n+1)+1` = `7n^3 + 4n^2 + 4n + 2`

## Conclusão
Somando-se todas as 3 partes do algoritmo que foram calculadas em separado, segue que:
- `4n^2 + 4n + 2` + `3n + 2` + `7n^3 + 4n^2 + 4n + 2` = `7n^3 + 8n^2 + 11n + 6`

Considerando o comportamento assintótico do algoritmo, ou seja, ignorando os elementos de menor peso e a constante que multiplica o elemento de maior peso, conclui-se que o algoritmo de floyd é O(n^3).
