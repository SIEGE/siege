/*
 * An example of use of SIEGE binary search trees.
 *
 * Yes, I know I went a *tad* overboard here, but I wanted a good
 * platform for testing these as well.
 */

#include <siege/siege.h>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NEWLINES "\r\n"
#define WHITESPACE  NEWLINES "\t\v "

static char* trim(char* str, const char* pattern)
{
    str[strcspn(str, pattern)] = 0;
    return str;
}
static char* trimNL(char* str)
{
    return trim(str, NEWLINES);
}
static char* trimSpace(char* str)
{
    return trim(str, WHITESPACE);
}
static char* skip(char* str, const char* pattern)
{
    return str + strspn(str, pattern);
}
static char* skipSpace(char* str)
{
    return skip(str, WHITESPACE);
}

static SGint SG_EXPORT _treeCmp(const void* a, const void* b)
{
    return strcmp(a, b);
}

static int insertItem(SGTree* tree, const char* str)
{
    if(sgTreeFindItem(tree, (void*)str))
        return 0;
    size_t len = strlen(str);
    char* item = malloc(len + 1);
    memcpy(item, str, len + 1);
    return sgTreeInsert(tree, item) ? 1 : -1;
}
static int removeItem(SGTree* tree, const char* str)
{
    if(!sgTreeFindItem(tree, (void*)str))
        return 0;
    sgTreeRemoveItem(tree, (void*)str);
    return 1;
}
static void printNode(SGTreeNode* node)
{
    if(!node) return;

    printNode(node->left);
    printf("\"%s\" ", (char*)node->item);
    printNode(node->right);
}
static void printTree(SGTree* tree)
{
    if(!tree->root)
        printf("<the tree is empty>");

    printNode(tree->root);
    printf("\n");
    fflush(stdout);
}
static void pprintNode(SGTreeNode* node, int depth, unsigned char* right)
{
    int i;
    for(i = 1; i < depth; i++)
        printf("%c ", right[i] ? ' ' : '|');

    if(depth > 0)
        putchar(right[depth] ? '\\' : '|');

    if(!node)
    {
        printf("\n");
        return;
    }

    if(depth > 0)
        putchar('-');

    printf("%s\n", (char*)node->item);
    if(!node->left && !node->right)
        return;
    right[depth + 1] = 0;
    pprintNode(node->left, depth + 1, right);
    right[depth + 1] = 1;
    pprintNode(node->right, depth + 1, right);
}
static void pprintTree(SGTree* tree)
{
    if(!tree->root)
    {
        printf("<the tree is empty>\n");
        return;
    }

    unsigned char right[256];
    right[0] = 1;

    pprintNode(tree->root, 0, right);
    printf("\n");
    fflush(stdout);
}
static void sprintNode(SGTreeNode* node, int depth, int pretty)
{
    int i;
    if(pretty)
    {
        for(i = 0; i < depth; i++)
            printf("  ");
    }

    if(!node)
    {
        printf("NIL");
        return;
    }

    if(!node->left && !node->right)
    {
        printf("%s", (char*)node->item);
        return;
    }

    printf("(%s%c", (char*)node->item, pretty ? '\n' : ' ');
    sprintNode(node->left, depth + 1, pretty);
    putchar(pretty ? '\n' : ' ');
    sprintNode(node->right, depth + 1, pretty);
    printf(")");
}
static void sprintTree(SGTree* tree, int pretty)
{
    sprintNode(tree->root, 0, pretty);
    printf("\n");
    fflush(stdout);
}

int main(void)
{
    char buf[1024];
    char* ptr;

    SGTree* tree = sgTreeCreate(_treeCmp);

    printf("Example of SIEGE binary trees");
    printf("----------------------------------------\n");

    int option;
    do
    {
        printf("Select a tree operation:\n");
        printf("+<elem> -- Add a new element\n");
        printf("-<elem> -- Delete an element\n");
        printf("?<elem> -- Query whether an element is present\n");
        printf("p       -- Print all elements in (strcmp) order\n");
        printf("pp      -- Pretty-print the tree\n");
        printf("s       -- Print the tree in a compact s-expression form\n");           // yes, I was bored.
        printf("ss      -- Pretty print the tree in a compact s-expression form\n");    // ...very bored.
        printf("\n");
        printf("q        -- Quit the program\n");
        printf("----------------------------------------\n");
        printf("Selection: "); fflush(stdout);
        fgets(buf, sizeof(buf), stdin);
        printf("\n");

        trimNL(buf);
        if(strstr(buf, "+") == buf)
            option = '+';
        else if(strstr(buf, "-") == buf)
            option = '-';
        else if(strstr(buf, "?") == buf)
            option = '?';
        else if(!strcmp(buf, "p") || !strcmp(buf, "P"))
            option = 'p';
        else if(!strcmp(buf, "pp") || !strcmp(buf, "pP") || !strcmp(buf, "Pp") || !strcmp(buf, "PP"))
            option = 'P';
        else if(!strcmp(buf, "s") || !strcmp(buf, "S"))
            option = 's';
        else if(!strcmp(buf, "ss") || !strcmp(buf, "sS") || !strcmp(buf, "Ss") || !strcmp(buf, "SS"))
            option = 'S';
        else if(!strcmp(buf, "q") || !strcmp(buf, "Q"))
            option = 'q';
        else
            option = 0;

        ptr = skipSpace(buf + 1);
        switch(option)
        {
            case '+':
                if(!strlen(ptr))
                {
                    printf("Error -- element must be a non-empty string!\n");
                    break;
                }
                switch(insertItem(tree, ptr))
                {
                    case 0: printf("Element '%s' already exists in the tree!\n", ptr); break;
                    case 1: printf("Element '%s' successfully added!\n", ptr); break;
                    default: printf("Error adding element '%s' -- probably out of memory!\n", ptr);
                }
                break;
            case '-':
                if(!strlen(ptr))
                {
                    printf("Error -- element must be a non-empty string!\n");
                    break;
                }
                switch(removeItem(tree, ptr))
                {
                    case 0: printf("There is no element '%s' in the tree!\n", ptr); break;
                    case 1: printf("Element '%s' successfully removed!\n", ptr); break;
                    default: printf("Error removing element '%s'!\n", ptr);
                }
                break;
            case '?':
                if(!strlen(ptr))
                {
                    printf("Error -- element must be a non-empty string!\n");
                    break;
                }
                if(sgTreeFindItem(tree, ptr))
                    printf("Element '%s' is present in the tree!\n", ptr);
                else
                    printf("Element '%s' is *NOT* present in the tree!\n", ptr);
                break;
            case 'p':
                printTree(tree);
                break;
            case 'P':
                pprintTree(tree);
                break;
            case 's':
                sprintTree(tree, 0);
                break;
            case 'S':
                sprintTree(tree, 1);
                break;
            case 'q':
                break; /* handled by the while() */
            default:
                printf("Invalid option '%s'!\n", trimSpace(buf));
                break;
        }
        printf("\n");
        fflush(stdout);
    }
    while(option != 'q');

    while(tree->root)
        removeItem(tree, tree->root->item);
    sgTreeDestroy(tree);

    return 0;
}
