//Aloca a primeira 
ArvAVL * aloca(int info){
	ArvAVL *arv
	arv = (ArvAvl*)malloc(sizeof(ArvAvl));
	arv->info = info;
	arv->altura = 0;
	arv->esq = arv->dir = NULL;
	return arv;
}

int altura (ArvAVL *a){
	if( a == NULL)
		return -1;
	return a->altura;
}



ArvAvl * insere_ArvAVL(ArvAVL * arv, int info ){
	if( arv == NULL ){
		arv = aloca(info);
	}
	else if( info < arv->info ){
		arv->esq = insere( info, arv->esq );
		if( altura( arv->esq ) - altura( arv->dir ) == 2 ){
			if( info < arv->esq->info )
				arv = rotacaoRR( arv );
			else
				arv = rotacaoLR( arv );
		}
	}
	else if( info > arv->info ){
		arv->dir = insere( info arv >dir);
		if( altura( arv->dir ) - altura( arv->esq ) == 2 ){
			if( info > arv->dir->info )
				arv = rotacaoLL( arv );
			else
				arv = rotacaoRL( arv );
		}
	}
	arv->altura = maior( altura( arv->esq ), altura( arv->dir ) ) + 1;
	return arv;
}
