#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <unistd.h>

#define button_submit 100//macro


HINSTANCE g_instance = 0;
HWND button_evento = 0;
void criar_labels(HWND hwnd);
void button_click(HWND hwnd);
void arquivo(HWND hwnd);
HWND hnome = 0;
HWND hidade = 0;
HWND hsexo = 0;

struct dados{
    char nome[20];
    char sexo[10];
    int idade[4];
}dado;

// função de eventos
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_PAINT:
//            printf( "WM_PAINT\n" );
            {
                PAINTSTRUCT ps;
                BeginPaint( hwnd, &ps );
                FillRect( GetDC( hwnd ), &ps.rcPaint, (HBRUSH) (COLOR_3DSHADOW));
                EndPaint( hwnd, &ps );
            }
            return 0;
        
        case WM_COMMAND:
            switch (wParam)
            {
            case button_submit:
                GetWindowText(hnome, dado.nome, 20);
                GetWindowText(hsexo, dado.sexo, 10);
                GetWindowText(hidade, dado.idade, 4);
                break;
            default:
                break;
            }

        case WM_CREATE:// função que cria função vinda de fora do escopo
            criar_labels(hwnd);
            button_click(hwnd);
            break;

        case WM_DESTROY: //importante, destroy, ele destroi a janela
            printf( "WM_DESTROY\n" );
            PostQuitMessage(0);
            return 0;
        
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
{
    const char * CLASS_NAME  = TEXT("CLASSE_WINDOWS");

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.style = CS_HREDRAW | CS_VREDRAW;
 

    RegisterClass(&wc);

    // cria a janela no Windows
    HWND hwnd = CreateWindowEx(
        0,                              // opcção de variavel
        CLASS_NAME,                     // classe window criada la em cima
        TEXT("Inicio de janela"),    //tituo da janela
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,          //função para que ela possa ou não ser sobreposta
        
        // Size and position
        CW_USEDEFAULT, 
        CW_USEDEFAULT, 
        400, // comprimento da janela, o width
        300, // o tamanho da jenale , heigh
        NULL,       // posição x
        NULL,       // posição y
        hInstance,  // Instance handle
        NULL        // memoria adicional
        );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow); // função para meu de fechar e minimixar a janela

    // Run the message loop.

    MSG msg = { };

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
void criar_labels(HWND hwnd) {
    CreateWindow(TEXT("STATIC"),TEXT("Insira os dados"), WS_VISIBLE | WS_CHILD | SS_SIMPLE, 150, 20, 300, 25, hwnd, (HMENU)1, NULL, NULL);
    CreateWindow(TEXT("STATIC"), TEXT("Nome"), WS_VISIBLE | WS_CHILD | SS_SIMPLE, 100, 50, 80, 25, hwnd, (HMENU)1, NULL, NULL);
    CreateWindow(TEXT("STATIC"), TEXT("Idade"), WS_VISIBLE | WS_CHILD | SS_SIMPLE, 100, 80, 80, 25, hwnd, (HMENU)2, NULL, NULL);
    CreateWindow(TEXT("STATIC"), TEXT("Sexo"), WS_VISIBLE | WS_CHILD | SS_SIMPLE, 100, 110, 80, 25, hwnd, (HMENU)3, NULL, NULL);
    hnome = CreateWindow(TEXT("EDIT"),TEXT(""), WS_VISIBLE | WS_CHILD  | WS_BORDER | WS_TABSTOP, 150, 50, 120, 20, hwnd, (HMENU)1, NULL, NULL);
    hidade = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 80, 120, 20, hwnd, (HMENU)2, NULL, NULL);
    hsexo = CreateWindow(TEXT("EDIT"), TEXT(""), WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 110, 120, 20, hwnd, (HMENU)3, NULL, NULL);
}
void button_click(HWND hwnd) {
   button_evento = CreateWindow(TEXT("BUTTON"),TEXT("cadastro"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 200, 100, 30, hwnd, (HMENU)button_submit, NULL, NULL);
}
void arquivo(HWND hwnd) {
    FILE *arquivoDados = fopen("dados.txt", "a");
    if (!arquivoDados) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }
    if (fprintf(arquivoDados, "%s;%d;%s\n", dado.nome, dado.idade, dado.sexo) < 0) {
        printf("Erro ao escrever dados\n");
        fclose(arquivoDados);
        return 1;
    }
    fclose(arquivoDados);
    CreateWindow(TEXT("STATIC"), TEXT("Dados salvos"), WS_VISIBLE | WS_CHILD | SS_SIMPLE, 100, 150, 80, 25, hwnd, (HMENU)3, NULL, NULL);
}
