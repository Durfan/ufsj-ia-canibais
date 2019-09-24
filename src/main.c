#include "./includes/main.h"

static void destroyWindowCb(void);
static gboolean closeWebViewCb(GtkWidget *window);


int main(int argc, char **argv) {

	static char home[1024];
	char apath[PATH_MAX];
    
	realpath("resources", apath); 
    printf("\n%s\n", apath);
    strcpy(home,"file://");
    strcat(home,apath);
	strcat(home,"/home.html");

	State start = setState(M,C);
 	State *hashmap = initMap();
	int stMppd,hSize = mapSize();

	// Initialize GTK+
    gtk_init(&argc, &argv);

	addState(start,hashmap);
	expand(start,hashmap);

   	for (int i=0; i < 5; i++) {
		for (int j=0; j < hSize; j++) {
			if (!hashmap[j].dinner)
				expand(hashmap[j],hashmap);
		}
	}

	prtMap(hashmap);

	stMppd = stMapp(hashmap);
	printf("\n Estados Mapeados: %d\n\n", stMppd);

	int **graph = iniArray(hSize,hSize);
	gGraph(hashmap,graph);
	genDot(hashmap,graph);
	pGraph(graph,hSize);


	// Create an 800x600 window that will contain the browser instance
    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

	// Create a browser instance
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

	// Put the browser area into the main window
    gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

	// Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
    g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);

	// Load a web page into the browser instance
    webkit_web_view_load_uri(webView,home);

	// Make sure that when the browser area becomes visible, it will get mouse
    // and keyboard events
    gtk_widget_grab_focus(GTK_WIDGET(webView));

    // Make sure the main window and all its contents are visible
    gtk_widget_show_all(main_window);

    // Run the main GTK+ event loop
    gtk_main();

	delArray(graph,hSize);
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