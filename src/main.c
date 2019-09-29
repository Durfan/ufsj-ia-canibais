#include "./includes/main.h"
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <sys/time.h>

static void destroyWindowCb(void);
static gboolean closeWebViewCb(GtkWidget *window);
GdkPixbuf *create_pixbuf(const gchar *filename);


int main(int argc, char **argv) {

    struct timeval tv1, tv2;

	static char home[1024];
	static char icon[1024];
	char apath[PATH_MAX];

    system("clear");
	realpath("resources", apath);
	printf(" DEBUG output -----\n");
    printf(" Resources Path: %s\n", apath);

	strcpy(home,"file://");
    strcat(home,apath);
	strcat(home,"/home.html");
	strcpy(icon,apath);
    strcat(icon,"/img/icon.png");


    gettimeofday(&tv1,NULL);
	largura();
    gettimeofday(&tv2,NULL);
    prtFOOclk(tv1,tv2);


    gettimeofday(&tv1,NULL);
	profund();
    gettimeofday(&tv2,NULL);
    prtFOOclk(tv1,tv2);


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
    webkit_web_view_load_uri(webView, home);

	// Make sure that when the browser area becomes visible, it will get mouse
    // and keyboard events
    gtk_widget_grab_focus(GTK_WIDGET(webView));

    // Make sure the main window and all its contents are visible
    gtk_widget_show_all(mainWindow);
	g_object_unref(appicon);

    // Run the main GTK+ event loop
    gtk_main();

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
