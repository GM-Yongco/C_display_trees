// ==========================================================================
// Description     : Code that will impress u ;)
// Author          : G.M. Yongco #BeSomeoneWhoCanStandByShinomiya
// Date            : ur my date uwu
// Description     : Actually just me playing around
// ==========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binary_trees.h"

int main(){
	section("START");

	char* al = alphabet_array();

	// INIT ==============================================================

	b_tree_p root = NULL;
	init(&root, al[0]);

	init(&(root->left), al[1]);
	init(&(root->rite), al[2]);
	
	init(&(root->left->left), al[3]);    
	init(&(root->left->rite), al[4]);
	init(&(root->rite->left), al[5]);
	// init(&(root->rite->rite), al[6]);

	// init(&(root->left->left->left), al[7]);
	// init(&(root->left->left->rite), al[8]);
	// init(&(root->left->rite->left), al[9]);
	// init(&(root->left->rite->rite), al[10]);
	// init(&(root->rite->left->left), al[11]);
	// init(&(root->rite->left->rite), al[12]);
	// init(&(root->rite->rite->left), al[13]);
	// init(&(root->rite->rite->rite), al[14]);
	
	// DISPLAY =============================================================

	section("TEST DEPTH");

	printf("%d\n", get_depth(root));
	printf("%d\n", get_depth(root->left));
	printf("%d\n", get_depth(root->left->left));
	printf("%d\n", get_depth(root->left->left->left));

	section("TEST BASE & HEIGHT");

	int i;
	for(i = 1; i<5; i++){
		// printf("%d\n", get_tree_display_base(i));
		// printf("%d\n", get_tree_display_height(i));
		printf("%d\n", get_tree_max_elemets(i));
		printf("\n\n");
	}

	section("PRINTING");
	display_ascii_tree(root);

	section("END");

	return 0;
}
