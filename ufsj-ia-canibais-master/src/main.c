#include "./includes/main.h"

static void destroyWindowCb(void);
static gboolean closeWebViewCb(GtkWidget *window);
GdkPixbuf *create_pixbuf(const gchar *filename);


int main(int argc, char **argv) {

	static char home[1024];
	static char icon[1024];
	char apath[PATH_MAX];

	realpath("resources", apath);
	printf(" DEBUG output -----\n");
    printf(" Resources Path: %s\n\n", apath);

	strcpy(home,"file://");
    strcat(home,apath);
	strcat(home,"/home.html");
	strcpy(icon,apath);
    strcat(icon,"/icon.png");

	State start = setState(M,C);
 	State *hashmap = initMap();
	int **graph = iniGraph();

	addState(start,hashmap);
	expand(start,hashmap);
   	for (int i=0; i < 5; i++) {
		for (int j=0; j < MAPSIZE; j++) {
			if (!hashmap[j].dinner) {
				expand(hashmap[j],hashmap);
			}
		}
	}

	prtMap(hashmap);

	int stMppd = stMapp(hashmap);
	printf("\n Estados Mapeados: %d\n\n", stMppd);
	gGraph(hashmap,graph);
	genDot(hashmap,graph);
	genViz(hashmap,graph);
	prtGraph(graph);

	// METODOS DE BUSCA IMPLEMENTADOS

	printf("\n---- Busca em profundidade:\n\n");
	State *hashma2p = initMap();
	int **grap2h = iniGraph();
	grap2h = depthFirstSearch(start, hashma2p);
	prtGraph(grap2h);
	free(hashma2p);
	delGraph(grap2h);


	printf("\n---- Busca em Largura:\n\n");
	State end; end.m = 0; end.c = 0; end.b = 0;
	State *hashma3p = initMap();
	int **grap3h = iniGraph();
	grap3h = breadthFirstSearch(start, hashma3p, end);
	prtGraph(grap3h);
	free(hashma3p);
	delGraph(grap3h);


	printf("\n Busca em largura bidirecional:\n\n");
	State *hashma4p = initMap();
	int **grap4h = iniGraph();
	State *hashma4p2 = initMap();
	grap4h = bidirectionalBredthSearch(start, end, hashma4p, hashma4p2);
	prtGraph(grap4h);
	free(hashma4p);
	delGraph(grap4h);



	printf("\n Busca em profundidade limitada - limit = 8:\n\n");
	State *hashma5p = initMap();
	int **grap5h = iniGraph();
	grap5h = limitedDepthSearch(start, hashma5p, 8);
	prtGraph(grap5h);
	delGraph(grap5h);
	free(hashma5p);



	// Initialize GTK+
    gtk_init(&argc, &argv);

	GtkWidget *mainWindow;
  	GdkPixbuf *appicon;

	// Create an 800x600 window that will contain the browser instance
    mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(mainWindow), "Missionarios vs. Canibais");
	gtk_window_set_default_size(GTK_WINDOW(mainWindow), 800, 600);
	gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);

	appicon = create_pixbuf(icon);
  	gtk_window_set_icon(GTK_WINDOW(mainWindow), appicon);

	// Create a browser instance
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

	// Put the browser area into the main window
    gtk_container_add(GTK_CONTAINER(mainWindow), GTK_WIDGET(webView));

	// Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(mainWindow, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), mainWindow);

	// Load a web page into the browser instance
    webkit_web_view_load_uri(webView,home);

	// Make sure that when the browser area becomes visible, it will get mouse
    // and keyboard events
    gtk_widget_grab_focus(GTK_WIDGET(webView));

    // Make sure the main window and all its contents are visible
    gtk_widget_show_all(mainWindow);
	g_object_unref(appicon);

    // Run the main GTK+ event loop
    gtk_main();

//	delGraph(graph);
	free(hashmap);

	return 0;
}

static void destroyWindowCb(void) {
    gtk_main_quit();
}

static gboolean closeWebViewCb(GtkWidget *window) {
    gtk_widget_destroy(window);
    return TRUE;
}

GdkPixbuf *create_pixbuf(const gchar *filename) {

   GdkPixbuf *pixbuf;
   GError *error = NULL;
   pixbuf = gdk_pixbuf_new_from_file(filename, &error);

   if (!pixbuf) {
      fprintf(stderr, "%s\n", error->message);
      g_error_free(error);
   }

   return pixbuf;
}
