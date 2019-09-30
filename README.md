# Os missionários e canibais

![Captura](https://github.com/Durfan/ufsj-ia-canibais/blob/master/docs/captura.png)

<img align="right" width="400" src="./resources/graphs/profund.svg">

Três missionários e três canibais estão em um lado de um rio, juntamente com um barco que pode levar uma ou duas pessoas. Descubra um meio de fazer todos atravessarem o rio sem deixar que um grupo de missionários de um lado fique em número menor que o número de canibais nesse mesmo lado do rio. Esse problema é famoso em IA porque foi assunto do primeiro artigo que abordou a formulação de problemas a partir de um ponto de vista analítico (Amarel, 1968).

## Instalação

``` bash
make
make debug # binario com debug
make clean # remover binario
./mvsc # binario
./plotGraph.sh # plot para dots gerados
```

## Dependências

* [GTK+](https://www.gtk.org/download/linux.php)
* [WebKitGTK](https://webkitgtk.org/)

## Saídas

* [./resources/graphs/*.dot](https://github.com/Durfan/ufsj-ia-canibais/blob/master/resources/graphs/) ::: [Graphviz Format](https://www.graphviz.org/)  
* [./resources/graphs/*.js](https://github.com/Durfan/ufsj-ia-canibais/blob/master/resources/graphs/) ::: [Force-directed graph](https://github.com/vasturiano/force-graph)

## Force Graph API

[Force-directed graph rendered on HTML5 canvas](https://github.com/vasturiano/force-graph)
