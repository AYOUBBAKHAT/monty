#include "monty.h"
/**
 * f_add - Additionne les deux éléments supérieurs de la pile.
 * @head: Pointeur vers le sommet de la pile.
 * @counter: Numéro de ligne où l'opération se produit.
 *
 * Description : Cette fonction additionne les deux éléments supérieurs de la pile.
 * Si la pile contient moins de deux éléments, elle affiche un message d'erreur
 * et quitte le programme.
 */
void f_add(stack_t **head, unsigned int counter)
{
	stack_t *h;
	int len = 0, aux;

	h = *head;
	while (h)
	{
		h = h->next;
		len++;
	}
	if (len < 2)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", counter);
		fclose(bus.file);
		free(bus.content);
		free_stack(*head);
		exit(EXIT_FAILURE);
	}
	h = *head;
	aux = h->n + h->next->n;
	h->next->n = aux;
	*head = h->next;
	free(h);
}
