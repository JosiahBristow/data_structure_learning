#ifndef BINARY_TREE
#define BINARY_TREE

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
        char val;
        struct TreeNode *left;
        struct TreeNode *right;
};

void create_tree(struct TreeNode **root, char *vals, int *index)
{
        char val;
        val = vals[*index];
        *index += 1;
        if (val == '#') {
                *root = NULL;
        } else {
                *root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
                (*root)->val = val;
                create_tree(&((*root)->left), vals, index);
                create_tree(&((*root)->right), vals, index);
        }
}

void pre_order(struct TreeNode *root)
{
        if (root == NULL)
                return;

        printf("%c\t", root->val);
        pre_order(root->left);
        pre_order(root->right);
}

void in_order(struct TreeNode *root)
{
        if (root == NULL)
                return;

        pre_order(root->left);
        printf("%c\t", root->val);
        pre_order(root->right);
}

void post_order(struct TreeNode *root)
{
        if (root == NULL)
                return;

        pre_order(root->left);
        pre_order(root->right);
        printf("%c\t", root->val);
}

#endif

int main(int argc, char *argv[])
{
        struct TreeNode *tree = NULL;
        int index = 0;
        create_tree(&tree, argv[1], &index);
        pre_order(tree);
        puts("\n");
        in_order(tree);
        puts("\n");
        post_order(tree);
        puts("\n");
        return EXIT_SUCCESS;
}
