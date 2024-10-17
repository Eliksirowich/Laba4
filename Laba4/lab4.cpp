#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
	int data;
	struct Node* left;
	struct Node* right;
};

struct Node* root = NULL;

struct Node* CreateTree(struct Node* root, struct Node* r, int data) {
	if (r == NULL)
	{
		r = (struct Node*)malloc(sizeof(struct Node));
		if (r == NULL)
		{
			printf("������ ��������� ������");
			exit(0);
		}

		r->left = NULL;
		r->right = NULL;
		r->data = data;
		if (root == NULL) return r;

		if (data > root->data)	root->left = r;
		else root->right = r;
		return r;
	}

	if (data > r->data)
		CreateTree(r, r->left, data);
	else
		CreateTree(r, r->right, data);

	return root;
}

void print_tree(struct Node* r, int l) {
	if (r == NULL) {
		return;
	}

	print_tree(r->right, l + 1);
	for (int i = 0; i < l; i++) {
		printf(" ");
	}

	printf("%d\n", r->data);
	print_tree(r->left, l + 1);
}


struct Node* find(struct Node* root, int data) {
	if (root == NULL) return NULL;  

	if (root->data == data) return root;
	if (data > root->data) return find(root->left, data);
	else return find(root->right, data);
}


int find_depth(struct Node* root, int data) {
	int depth = 0;
	struct Node* current = root;

	while (current != NULL) {
		if (current->data == data) {
			return depth;  
		}
		depth++;  

		if (data > current->data) {
			current = current->left; 
		}
		else {
			current = current->right; 
		}
	}

	return -1;  
}

int count(struct Node* root, int data, int cnt) {
	if (root->data == data) cnt++;
	if (root->data >= data && root->right != NULL) cnt = count(root->right, data, cnt);
	else if (root->left != NULL)  cnt = count(root->left, data, cnt);
	else return cnt;

	return cnt;
}

int main() {
	setlocale(LC_ALL, "Rus");
	int D, number, start = 1;

	printf("-1 - ��������� ���������� ������\n");
	while (start) {
		printf("������� �����: ");
		scanf_s("%d", &D);
		if (D == -1) {
			printf("���������� ������ ��������\n\n");
			start = 0;
		}
		else
			root = CreateTree(root, root, D);
	}

	print_tree(root, 0);
	printf("����� �������� number\n");
	scanf_s("%d", &number);

	int cnt = count(root, number, 0);
	printf("������� %d\n", cnt);

	struct Node* r = find(root, number);

	if (r) {
		printf("������ %d\n", r->data);
		int depth = find_depth(root, number);
		printf("������� �������� %d: %d\n", number, depth);
	}
	else {
		printf("������� �� ������\n");
	}

	scanf_s("%d", &D);
	return 0;
}

