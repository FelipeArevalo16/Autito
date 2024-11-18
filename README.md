Auto con mqtt

Este auto tiene 2 codigos;
El autonomo y el controlado.

Con el Autonomo el auto avanza de forma automatica hasta que se encuentra con un obstaculo a 20 centimetros,
medido por un sensor de proximidad SR-04. Al detectar esta distancia el buzzer avisa con un sonido y hace que el auto gire
hacia la derecha para despues retroceder hasta que el sensor mida una distacia superior a los 20 centimetros para seguir su camino.

El Controlado usa un protocolo mqtt para conectarse con el telefono, usando la red local de este mismo.
Se usa la aplicacion IoT Mqtt Panel para controlar el auto, usando los topicos declarados en el codigo, que
responden a 1 para activar y 0 para desactivar.

tiene 5 funciones que utilizan los switch de la aplicacion;
st/01;
Avanza
st/02;
Retrocede
st/03; 
Gira a la izquierda
st/04;
Gira a la Derecha
st/05;
Reproduce una melodia con un buzzer.
