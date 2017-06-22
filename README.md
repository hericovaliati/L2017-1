# L2017-1
Compilador para a Linguagem L2017-1

Necessário a instalação do flex e bison.

No ubuntu:

sudo apt-get install flex

sudo apt-get install bison

make

e

./L2017-1 -i <entrada.pas> -o <saida.<.bin|.mepa>> -c <bin|inter>

-c bin -> gera a tradução do código intermediário

-c inter -> gera código intermediário 

L2017-1 é um subconjunto da linguagem Pascal

O compilador L2017-1c não está 100%, mas os conceitos básicos para seu funcionamento foram todos implementados

Sintam-se a vontade para contribuir:
    1° Mantendo o código claro, já que é um projeto com fins didáticos
    2° Sempre testando-o
