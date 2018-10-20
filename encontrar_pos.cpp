data encontrar_min(min_p,max_p, pos_st, s_t){ //pos_st empieza siendo 0 en la primera llamada
	
	while(s_t[pos_st].pos[0] != min_p) // recorro hasta el nivel mas alto que empiece con la pos minima pedida
		pos_st++;

	if(max_p == s_t[pos_st].pos[1])	// Si estoy en el bloque que tiene como minimo y maximo los pedidos lo devuelvo.
		return s_t[pos_st];

	else if(max_p > s_t[pos_st].pos[1]) // Si el maximo pedido es mayor al maximo del nivel mas alto que empieza con la pos minima pedida
		encontrar_min(s_t[pos_st].pos[1], max_p, pos_st+1, s_t); // Llamo a la funcion a partir de la posicion siguiente a la que me quede utilizando como minimo el maximo del intervalo anterior.

	else
		encontrar_min(min_p, max_p, i+1, s_t); // Si el maximo pedido esta contenido en el intervalo grande cuya pos inicial es igual a la pedida, sigo buscando el proximo nivel con esa pos init
											   // fijandome si esa vez coincide tambien la posicion final con la max pedida.


	// ACA CREO QUE DEBERIA UTILIZAR UN PARAMETRO MAS PARA PASARLE EL BLOQUE A COMPARAR.
	return un data hecho a partir de los dos datas a analizar. 
}	