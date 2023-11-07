//==========================================================================
//Description     : Code that will impress u ;)
//Author          : G.M. Yongco #BeSomeoneWhoCanStandByShinomiya
//Date            : ur my date uwu
//==========================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =======================================================================
// TEMPLATE MISC 
// =======================================================================

typedef enum boolean{FALSE, TRUE}BOOLEAN;

void section(char* message){
	int count = 43;			//addintional 3 for the (\n)s and the \0
	char new_string[count];
	
	int i;
	for(i = 0; i<count; i++){
		new_string[i] = '-';
	}

	new_string[count-1] = '\0';
	new_string[count-2] = '\n';
	new_string[0] = '\n';

	int len = strlen(message);
	memcpy(new_string + 2, message, len);
	new_string[len+2] = ' ';
	new_string[1] = ' ';

	printf("%s", new_string);
}

// =======================================================================
// STRUCTS
// =======================================================================

typedef struct node_b_tree{
	char data;
	struct node_b_tree* left;
	struct node_b_tree* rite;
}b_tree, *b_tree_p;

// =======================================================================
// FUNCTIONS CORE 1
// =======================================================================

void init(b_tree_p* node, char new_data){
	b_tree_p new_node = (b_tree_p)malloc(sizeof(b_tree));
	new_node->left = NULL;
	new_node->rite = NULL;
	new_node->data = new_data;
	
	*node = new_node;
}

char* alphabet_array(){
	char* ret_val = (char*)malloc(sizeof(char)*27);
	ret_val[26] = '\0';

	char start = 'A';
	int x;
	for(x = 0; x<26; x++){
		ret_val[x] = start + x;

	}

	return ret_val;
}

void display_inorder(b_tree_p root){
	if(root != NULL){
		display_inorder(root->left);
		printf("%c", root->data);
		display_inorder(root->rite);
	}
}

// =======================================================================
// FUNCTIONS CORE 2
// =======================================================================

int get_depth(b_tree_p root){
	int ret_val = 0;

	// can prolly be ternaried but it wont be readable in this context
	// me thinks
	if(root != NULL){
		int left_depth = get_depth(root->left);
		int rite_depth = get_depth(root->rite);
		int bigger = 0;

		if(left_depth>rite_depth){
			bigger = left_depth;
		}else{
			bigger = rite_depth;
		}
		ret_val = bigger + 1;
	}
	return ret_val;
}

int get_tree_display_base(int depth){
	int ret_val = 1;
	if(depth > 1){
		ret_val = (get_tree_display_base(depth-1)* 2) + 3;
	}
	return ret_val;
}
int get_tree_display_height(int depth){
	return (depth*2)-1;
}

int get_tree_max_elemets(int depth){
	return (1<<depth)-1;
	// basically 2^(depth-1)
}

// =======================================================================
// FUNCTIONS CORE 3
// =======================================================================


b_tree_p* store_in_heap(b_tree_p root){
	int count = get_tree_max_elemets(get_depth(root));
	b_tree_p* heap = (b_tree_p*)malloc(sizeof(b_tree_p) * count);
	
	heap[0] = root;
	int i;
	for(i = 0; (i<count) && (((i*2) + 1) < count) ; i++){
		if(heap[i] !=NULL){
			heap[(i*2) + 1] = heap[i]->left;
			heap[(i*2) + 2] = heap[i]->rite;
		}else{
			heap[(i*2) + 1] = NULL;
			heap[(i*2) + 2] = NULL;
		}
	}
	
	return heap;
}

void print_heap(b_tree_p* heap, int count){
	int i;
	for(i = 0; (i<count); i++){
		if(heap[i] == NULL){
			printf("[%d] = NULL\n", i);	
		}else{
			printf("[%d] = %c\n", i, heap[i]->data);	
		}
	}
}

// =======================================================================
// FUNCTIONS CORE 4
// =======================================================================

int power_minus_one(int elem_num){
	elem_num = elem_num +1;
	
	int power = 1;
	int compare = 2;
	while( compare <= elem_num){
		power++;
		compare = 1 << power;
	}
	return(power-1);
}

int mod_two_power(int elem_num){
	elem_num = elem_num +1;
	
	int power = 1;
	int compare = 2;
	while( compare <= elem_num){
		power++;
		compare = 1 << power;
	}
	return elem_num - (compare>>1);
}

int num_coords_height(int elem_num){
	return(power_minus_one(elem_num)*2);
}

int num_coords_width(int elem_num, int depth){
	int ret_val = get_tree_display_base(depth - power_minus_one(elem_num))/2;
	int additional = ((get_tree_display_base(depth - power_minus_one(elem_num) + 1)/2) + 2) * mod_two_power(elem_num);
	
	ret_val += additional;

	return ret_val;
}

// =======================================================================
// FUNCTIONS CORE 5
// =======================================================================

void display_ascii_tree(b_tree_p root){
	int depth = get_depth(root);
	int width = get_tree_display_base(depth);
	int height = get_tree_display_height(depth);

	// CREATING THE DIAGRAM =========================================

	char diagram[height][width+1]; // +1 for the '\0'
	
	//background
	int i;
	for(i = 0; i<height; i++){
		memset(diagram[i], ' ', sizeof(char)* width);
		diagram[i][width] = '\0';
	}

	//store conveniently
	b_tree_p* heap = store_in_heap(root);

	//putting in values
	int count = get_tree_max_elemets(depth);
	int coord_y;
	int coord_x;
	char THE_CHAR;
	for(i = 0; (i<count); i++){
		THE_CHAR = ' ';	//default if null
		
		if(heap[i] != NULL){
			THE_CHAR = heap[i]->data;
		}
		coord_y = num_coords_height(i);
		coord_x = num_coords_width(i, depth);
		diagram[coord_y][coord_x] = THE_CHAR;

		//putting in the branches thingy
		if(i > 0 && heap[i] != NULL){
			coord_y -= 1 ;
			coord_x = (num_coords_width((i-1)/2, depth) + coord_x)/2;
			
			THE_CHAR = '/';
			(i%2 == 1)?(THE_CHAR = '/'):(THE_CHAR = '\\');
			diagram[coord_y][coord_x] = THE_CHAR;
		}

		// int j;
		// for(j = 0; j<height; j++){
		// 	printf("%s\n", diagram[j]);
		// }
	}

	// DISPLAYING THE STRINGS =======================================
	for(i = 0; i<height; i++){
		printf("%s\n", diagram[i]);
	}
}