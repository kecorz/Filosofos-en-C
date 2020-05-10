
 ************ Problema de los cinco filósofos de E. Dikjstra**************


Cinco filósofos se sientan alrededor de una mesa redonda para comer un plato de fideos. Cada filósofo cuenta con un tenedor a la izquierda de su plato, pero para comer los fideos necesita usar dos tenedores. Cuando un filósofo tiene hambre, éste coge primero el tenedor de la izquierda y luego el tenedor de la derecha.

Los filósofos comerán durante un determinado tiempo y luego de comer se sentirán llenos. Un filósofo lleno no come, sino que piensa hasta que le de hambre de nuevo, entonces intentará tomar ambos tenedores y comer. Después de un tiempo sin comer, un filósofo hambriento muere de hambre.

El problema consiste en encontrar un algoritmo que nos permita resolver el dilema de los filósofos, donde todos los filósofos deben de comer, considerando que primero tomaran el tenedor de la izquierda y despues el de la derecha.


******* Requisitos ********

Las librerias que se ocuparon en el desarrollo de C son las estánadares, por lo que no es necesario descargar ningún otro requerimiento.

El programa se compila de la siguiente manera:

gcc -pthread -o filosofos filosofos.c

Y se ejecuta de la siguiente manera:

./filosofos [tiempo en segundos] [numero de filosofos]

****************************

Autor: Corella Pérez Elda
