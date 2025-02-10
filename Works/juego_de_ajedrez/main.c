#include <windows.h>
#include <stdio.h>
#include <stdbool.h>

// Constantes del juego
#define BOARD_SIZE 8 	// Tamaño del tablero de ajedrez (8x8).
#define CELL_SIZE 80	// Tamaño de cada celda del tablero en píxeles.
#define NUM_PIECES 12	// Número de tipos de piezas distintas (blancas y negras).

// Variables globales
HINSTANCE g_hInst;              // Instancia de la aplicación.
HWND g_hWnd;                    // Handle para la ventana principal.
POINT selectedCell = {-1, -1};  // Casilla seleccionada. (-1, -1) indica que no hay selección.

// Enumeración para los tipos de piezas de ajedrez.
typedef enum {
    EMPTY,    // Casilla vacía.
    PAWN,     // Peón.
    ROOK,     // Torre.
    KNIGHT,   // Caballo.
    BISHOP,   // Alfil.
    QUEEN,    // Reina.
    KING      // Rey.
} PieceType;

// Enumeración para los colores de las piezas de ajedrez.
typedef enum {
    NONE,   // Sin color (casilla vacía).
    WHITE,  // Blanco.
    BLACK   // Negro.
} PieceColor;

// Estructura que representa una pieza de ajedrez.
typedef struct {
    PieceType type;   // Tipo de pieza.
    PieceColor color; // Color de la pieza.
} ChessPiece;

// Tablero de ajedrez representado como una matriz de 8x8.
ChessPiece board[BOARD_SIZE][BOARD_SIZE];

PieceColor currentTurn = WHITE;  // Turno actual del juego. Comienza con blancas.

// Handles para las imágenes de las piezas de ajedrez.
HBITMAP hWhitePawn, hBlackPawn; 	// Peones
HBITMAP hWhiteRook, hBlackRook; 	// Torres
HBITMAP hWhiteKnight, hBlackKnight; // Caballos
HBITMAP hWhiteBishop, hBlackBishop; // Alfiles
HBITMAP hWhiteQueen, hBlackQueen; 	// Reinas
HBITMAP hWhiteKing, hBlackKing; 	// Reyes

// Arreglo que almacena los punteros a las imágenes de las piezas.
HBITMAP* ImagesPieces[NUM_PIECES] = {
    &hWhitePawn, &hBlackPawn,
	&hWhiteRook, &hBlackRook,
	&hWhiteKnight, &hBlackKnight,
    &hWhiteBishop, &hBlackBishop,
	&hWhiteQueen, &hBlackQueen,
	&hWhiteKing, &hBlackKing
};

// Nombres de los archivos BMP que contienen las imágenes de las piezas.
const char* filenamePieces[NUM_PIECES] = {
    "PeonBlanca.bmp", "PeonNegra.bmp",
	"TorreBlanca.bmp", "TorreNegra.bmp",
	"CaballoBlanca.bmp", "CaballoNegra.bmp",
    "AlfilBlanca.bmp", "AlfilNegra.bmp",
	"ReinaBlanca.bmp", "ReinaNegra.bmp",
	"ReyBlanca.bmp", "ReyNegra.bmp"
};

// Prototipos
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void LoadImagePieces(); // Encargada de cargar los imagenes .bmp de las piezas de ajedrez.
void InitializeBoard(); // Encargada de inicializar el tablero con las piezas a nivel de tipos estructural.
void DrawBoard(HDC hdc); // Encargada de dibujar el tablero y la logica de dibujado al seleccionar.
void DrawPiece(HDC hdc, ChessPiece piece, int x, int y); // Encargada de dibujar las piezas/imagenes dentro del tablero.

// Todas las funciones a continuacion se encargan de validad los movimientos de las piezas.
bool IsValidMove(POINT from, POINT to);
bool IsValidPawnMove(ChessPiece piece, POINT from, POINT to, int dx, int dy, ChessPiece target);
bool IsValidRookMove(POINT from, POINT to, int dx, int dy);
bool IsValidBishopMove(POINT from, POINT to, int dx, int dy);
bool IsValidKnightMove(int dx, int dy);
bool IsValidQueenMove(POINT from, POINT to, int dx, int dy);
bool IsValidKingMove(int dx, int dy);

// Encargadas de obtener la posicion del rey y determinar si es JaqueMate.
POINT GetKingPosition(PieceColor color);
void CheckMate(PieceColor color);

// Encargada de actualizar el tablero realizando el movimiento que el usuario indico siempre que sea correcto.
void MovePiece(POINT src, POINT dest);

// Punto de entrada principal para la aplicación de Windows.
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Guardar la instancia de la aplicación.
    g_hInst = hInstance;

    // Definir y registrar la clase de ventana.
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;  // Procedimiento de ventana.
    wc.hInstance = hInstance;    // Instancia actual.
    wc.lpszClassName = "ChessGame";  // Nombre de la clase.

    RegisterClass(&wc);

    // Crear la ventana principal.
    g_hWnd = CreateWindowEx(
        0,								// Estilo extendido de ventana.
        "ChessGame",					// Nombre de la clase.
        "ChessGame",					// Título de la ventana.
        WS_OVERLAPPEDWINDOW,			// Estilo de ventana.
        CW_USEDEFAULT, CW_USEDEFAULT,	// Posición inicial de la ventana.
        BOARD_SIZE * CELL_SIZE + 16,	// Ancho de la ventana (tablero + bordes).
        BOARD_SIZE * CELL_SIZE + 39 + CELL_SIZE,  // Alto de la ventana (tablero + bordes + espacio extra).
        NULL, NULL,						// Sin ventana padre ni menú.
        hInstance,						// Instancia de la aplicación.
        NULL							// Sin datos adicionales.
    );

    // Verificar si la ventana fue creada correctamente.
    if (g_hWnd == NULL) return 0;

    // Inicializar el tablero de ajedrez.
    InitializeBoard();

    // Mostrar la ventana principal.
    ShowWindow(g_hWnd, nCmdShow);

    // Bucle de mensajes de Windows.
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);	// Traducir mensajes de teclado.
        DispatchMessage(&msg);	// Enviar mensajes a la ventana.
    }

    return 0;  // Finalizar aplicación.
}

// Procedimiento de ventana: maneja los mensajes enviados a la ventana principal.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            // Manejar el evento de repintado de la ventana.
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps); // Comenzar el proceso de dibujo.
            DrawBoard(hdc);					 // Dibujar el tablero de ajedrez.
            EndPaint(hwnd, &ps);			 // Finalizar el proceso de dibujo.
            break;
        }

        case WM_LBUTTONDOWN: {
            // Manejar el clic izquierdo del ratón.
            int x = LOWORD(lParam) / CELL_SIZE; // Obtener la coordenada X de la celda clicada.
            int y = HIWORD(lParam) / CELL_SIZE; // Obtener la coordenada Y de la celda clicada.

            // Validar que el clic está dentro de los límites del tablero.
            if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                if (selectedCell.x == -1) {
					// Si no hay una celda seleccionada, seleccionar la actual.
                    selectedCell.x = x;
                    selectedCell.y = y;
                } else {
                    // Si ya hay una celda seleccionada, intentar mover la pieza.
                    POINT from = selectedCell;	// Celda de origen.
                    POINT to = {x, y};			// Celda de destino.

                    if (IsValidMove(from, to)) {
                        MovePiece(from, to); // Mover la pieza si el movimiento es válido.
                    }

                    // Deseleccionar la celda después del movimiento.
                    selectedCell.x = -1;
                    selectedCell.y = -1;
                }

                // Solicitar el redibujado del tablero.
                InvalidateRect(hwnd, NULL, TRUE);	// Marcar toda la ventana para redibujar.
                UpdateWindow(hwnd);					// Forzar el redibujado inmediato.
            }
            break;
        }

        case WM_DESTROY:
            // Manejar el cierre de la ventana.
            PostQuitMessage(0); // Finalizar la aplicación.
            break;

        default:
            // Procesar todos los mensajes no manejados.
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0; // Retornar 0 si el mensaje fue manejado.
}

void LoadImagePieces() {
    char path[256];

    // Cargar todas las imágenes
    for (int i = 0; i < NUM_PIECES; i++) {
        // Construir la ruta completa del archivo
        snprintf(path, sizeof(path), "images/%s", filenamePieces[i]);

        // Cargar la imagen y asignarla a la variable correspondiente
        *(ImagesPieces[i]) = (HBITMAP)LoadImage(NULL, path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        
        if (*(ImagesPieces[i]) == NULL) {
            // Si ocurre un error al cargar la imagen, mostrar un mensaje
            char errorMessage[256];
            snprintf(errorMessage, sizeof(errorMessage), "Error loading image: %s", path);
            MessageBox(NULL, errorMessage, "Error", MB_OK | MB_ICONERROR);
        }
    }
}

// Inicializar el tablero con las piezas en su posición inicial
void InitializeBoard() {
    // Cargar imágenes
    LoadImagePieces();

    // Inicializar el tablero con las piezas
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            board[y][x].type = EMPTY;
            board[y][x].color = NONE;
        }
    }

    // Piezas iniciales
    for (int x = 0; x < BOARD_SIZE; x++) {
        board[1][x].type = PAWN;
        board[1][x].color = BLACK;
        board[6][x].type = PAWN;
        board[6][x].color = WHITE;
    }

    PieceType backRow[] = {ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK};
    for (int x = 0; x < BOARD_SIZE; x++) {
        board[0][x].type = backRow[x];
        board[0][x].color = BLACK;
        board[7][x].type = backRow[x];
        board[7][x].color = WHITE;
    }
}

// Dibujar el tablero
void DrawBoard(HDC hdc) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            RECT cell = {x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE};
            
            // Dibujar el color de la casilla
            HBRUSH brush = ((x + y) % 2 == 0) ? CreateSolidBrush(RGB(240, 217, 181)) : CreateSolidBrush(RGB(181, 136, 99));
            FillRect(hdc, &cell, brush);
            DeleteObject(brush);

            // Dibujar borde si la celda está seleccionada
            if (selectedCell.x == x && selectedCell.y == y) {
                // Determinar el color del borde según el turno
                ChessPiece piece = board[y][x]; // Obtener la pieza en la casilla
                HPEN hPen;
				
                if (piece.type == EMPTY) { // Casilla vacia -> borde gris.
					hPen = CreatePen(PS_SOLID, 4, RGB(211, 211, 211));
				} else if (currentTurn == piece.color) { // Pieza del color correspondiente al turno -> borde verde.
                    hPen = CreatePen(PS_SOLID, 4, RGB(0, 255, 0));
                } else { // Pieza del color contrario al turno -> borde rojo.
                    hPen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
                }

                // Dibujar el borde
                HGDIOBJ oldPen = SelectObject(hdc, hPen);
                HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH)); // Sin relleno

                Rectangle(hdc, cell.left, cell.top, cell.right, cell.bottom);
                SelectObject(hdc, oldPen);
                SelectObject(hdc, oldBrush);
                DeleteObject(hPen);
            }
            
            // Dibujar la pieza
            DrawPiece(hdc, board[y][x], x * CELL_SIZE, y * CELL_SIZE);
        }
    }
    
    // Dibujar la fila para el turno
    RECT turnRect = {0, BOARD_SIZE * CELL_SIZE, BOARD_SIZE * CELL_SIZE, (BOARD_SIZE + 1) * CELL_SIZE};

    // Seleccionar el color de fondo y texto dependiendo del turno
    HBRUSH turnBrush;
    COLORREF textColor;
    const char* turnText;

    if (currentTurn == WHITE) {
        turnBrush = CreateSolidBrush(RGB(255, 255, 255));  // Blanco
        textColor = RGB(0, 0, 0);  // Negro
        turnText = "Piece Turn: White";
    } else {
        turnBrush = CreateSolidBrush(RGB(0, 0, 0));  // Negro
        textColor = RGB(255, 255, 255);  // Blanco
        turnText = "Piece Turn: Black";
    }

    // Dibujar el fondo de la fila
    FillRect(hdc, &turnRect, turnBrush);
    DeleteObject(turnBrush);

    // Dibujar el texto
    SetTextColor(hdc, textColor);
    SetBkMode(hdc, TRANSPARENT);  // Fondo transparente para que no cubra el fondo de la celda
    DrawText(hdc, turnText, -1, &turnRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

// Dibujar una pieza en el tablero
void DrawPiece(HDC hdc, ChessPiece piece, int x, int y) {
    if (piece.type == EMPTY) return;

    HBITMAP hBitmap = NULL;

    // Seleccionar la imagen correcta dependiendo del tipo y color de la pieza
    switch (piece.type) {
        case PAWN:
            hBitmap = (piece.color == WHITE) ? hWhitePawn : hBlackPawn;
            break;
        case ROOK:
            hBitmap = (piece.color == WHITE) ? hWhiteRook : hBlackRook;
            break;
        case KNIGHT:
            hBitmap = (piece.color == WHITE) ? hWhiteKnight : hBlackKnight;
            break;
        case BISHOP:
            hBitmap = (piece.color == WHITE) ? hWhiteBishop : hBlackBishop;
            break;
        case QUEEN:
            hBitmap = (piece.color == WHITE) ? hWhiteQueen : hBlackQueen;
            break;
        case KING:
            hBitmap = (piece.color == WHITE) ? hWhiteKing : hBlackKing;
            break;
    }
    
    // Dibujar la imagen en la casilla correspondiente
    if (hBitmap != NULL) {
        // Crear un contexto compatible para dibujar la imagen
        HDC hMemDC = CreateCompatibleDC(hdc);
        SelectObject(hMemDC, hBitmap);

        // Obtener las dimensiones de la imagen
        BITMAP bmp;
        GetObject(hBitmap, sizeof(bmp), &bmp);

        // Calcular el desplazamiento para centrar la imagen en la celda
        int dx = (CELL_SIZE - bmp.bmWidth) / 2;
        int dy = (CELL_SIZE - bmp.bmHeight) / 2;

        // Dibujar la imagen centrada en la celda
        BitBlt(hdc, x + dx, y + dy, bmp.bmWidth, bmp.bmHeight, hMemDC, 0, 0, SRCCOPY);

        // Liberar recursos
        DeleteDC(hMemDC);
    }
}

bool IsValidMove(POINT from, POINT to) {
    ChessPiece piece = board[from.y][from.x];
	ChessPiece target = board[to.y][to.x];

    if (piece.color != currentTurn) {
        return false;  // El jugador no puede mover piezas del color contrario
    }

    if (to.x < 0 || to.x >= BOARD_SIZE || to.y < 0 || to.y >= BOARD_SIZE) {
        return false;
    }

    if (piece.type == EMPTY) {
        return false;
    }

    if (target.color == piece.color) {
        return false;  // No se puede capturar una pieza del mismo color
    }

    // Diferenciar las reglas según el tipo de pieza
    int dx = to.x - from.x;
    int dy = to.y - from.y;

    switch (piece.type) {
        case PAWN:
            return IsValidPawnMove(piece, from, to, dx, dy, target);
        case ROOK:
            return IsValidRookMove(from, to, dx, dy);
        case KNIGHT:
            return IsValidKnightMove(dx, dy);
        case BISHOP:
            return IsValidBishopMove(from, to, dx, dy);
        case QUEEN:
            return IsValidQueenMove(from, to, dx, dy);
        case KING:
            return IsValidKingMove(dx, dy);
        default:
            return false;
    }
}

bool IsValidPawnMove(ChessPiece piece, POINT from, POINT to, int dx, int dy, ChessPiece target) {
    int direction = (piece.color == WHITE) ? -1 : 1;  // Blancas avanzan hacia arriba, negras hacia abajo

    // Movimiento hacia adelante
    if (dx == 0 && dy == direction && target.type == EMPTY) {
        return true;
    }

    // Movimiento doble en el primer turno
    if (dx == 0 && dy == 2 * direction && from.y == ((piece.color == WHITE) ? 6 : 1) && target.type == EMPTY) {
        return true;
    }

    // Captura en diagonal
    if (abs(dx) == 1 && dy == direction && target.type != EMPTY && target.color != piece.color) {
        return true;
    }

    return false;
}

bool IsValidRookMove(POINT from, POINT to, int dx, int dy) {
    if (dx != 0 && dy != 0) {
        return false;  // Solo movimientos en línea recta
    }

    // Verificar que no haya piezas en el camino
    int stepX = (dx != 0) ? (dx / abs(dx)) : 0;
    int stepY = (dy != 0) ? (dy / abs(dy)) : 0;

    for (int x = from.x + stepX, y = from.y + stepY; x != to.x || y != to.y; x += stepX, y += stepY) {
        if (board[y][x].type != EMPTY) {
            return false;
        }
    }

    return true;
}

bool IsValidBishopMove(POINT from, POINT to, int dx, int dy) {
    if (abs(dx) != abs(dy)) {
        return false;  // Movimiento en diagonal
    }

    // Verificar que no haya piezas en el camino
    int stepX = dx / abs(dx);
    int stepY = dy / abs(dy);

    for (int x = from.x + stepX, y = from.y + stepY; x != to.x || y != to.y; x += stepX, y += stepY) {
        if (board[y][x].type != EMPTY) {
            return false;
        }
    }

    return true;
}

bool IsValidKnightMove(int dx, int dy) {
    return (abs(dx) == 2 && abs(dy) == 1) || (abs(dx) == 1 && abs(dy) == 2);
}

bool IsValidQueenMove(POINT from, POINT to, int dx, int dy) {
    return IsValidRookMove(from, to, dx, dy) || IsValidBishopMove(from, to, dx, dy);
}

bool IsValidKingMove(int dx, int dy) {
    return abs(dx) <= 1 && abs(dy) <= 1;
}

// Función que devuelve la posición del rey si está presente, o (-1, -1) si no está presente
POINT GetKingPosition(PieceColor color) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board[y][x].type == KING && board[y][x].color == color) {
                return (POINT){x, y};  // Devuelve la posición del rey
            }
        }
    }
    return (POINT){-1, -1};  // Si el rey no está presente, devuelve (-1, -1)
}

// Luego del Jaquemate mostrar mensaje ganador y cerrar el juego.
void CheckMate(PieceColor color) {
    // Verificar si el rey está presente en el tablero
    POINT kingPosition = GetKingPosition(color);
    if (kingPosition.x == -1 && kingPosition.y == -1) {
        // Si el rey no está en el tablero, el jugador ha perdido
        if (color == WHITE) {
            MessageBox(g_hWnd, "¡El rey blanco ha sido eliminado! Las Negras ganaron.", "Fin del Juego", MB_OK);
        } else {
            MessageBox(g_hWnd, "¡El rey negro ha sido eliminado! Las Blancas ganaron.", "Fin del Juego", MB_OK);
        }
        PostQuitMessage(0);  // Cerrar el juego si el rey ha sido eliminado
    }
}

// Después de mover una pieza, verificar si el rey oponente sigue en el tablero.
void MovePiece(POINT src, POINT dest) {
    ChessPiece piece = board[src.y][src.x];
    //ChessPiece target = board[dest.y][dest.x];

    // Verificar que la casilla de origen contiene una pieza válida
    if (piece.type == EMPTY) {
        MessageBox(g_hWnd, "No hay ninguna pieza en la casilla seleccionada.", "Movimiento Inválido", MB_OK);
    }

    // Verificar si la pieza pertenece al jugador actual
    if (piece.color != currentTurn) {
        MessageBox(g_hWnd, "No es tu turno.", "Movimiento Inválido", MB_OK);
    }

    // Verificar si el movimiento es válido para la pieza
    if (!IsValidMove(src, dest)) {
        MessageBox(g_hWnd, "Movimiento no válido para esta pieza.", "Movimiento Inválido", MB_OK);
    }

    // Movimiento válido: actualizar el tablero
    board[src.y][src.x] = (ChessPiece){EMPTY, NONE};
    board[dest.y][dest.x] = piece;    
    
    // Comprobar si el movimiento eliminó al rey contrario
    CheckMate(currentTurn == WHITE ? BLACK : WHITE);

	// Cambiamos el turno
	currentTurn = (currentTurn == WHITE) ? BLACK : WHITE;
}


