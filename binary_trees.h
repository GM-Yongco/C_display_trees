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
	int count = 43;			//additional 3 for the (\n)s and the \0
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



void display_ascii_tree(b_tree_p root){
	int depth = get_depth(root);
	int width = get_tree_display_base(depth);
	int height = get_tree_display_height(depth);

	// CREATING THE DIAGRAM =========================================

	char diagram[height][width+1]; // +1 for the '\0'
	
	//background
	int i;
	for(i = 0; i<height; i++){
		memset(diagram[i], '-', sizeof(char)* width);
		diagram[i][width] = '\0';
	}

	//putting in values
	diagram[0][(width/2)] = root->data;

	// DISPLAYING THE STRINGS =======================================
	for(i = 0; i<height; i++){
		printf("%s\n", diagram[i]);
	}
}