#include "./includes/main.h"
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#include <linux/limits.h>

static void destroyWindowCb(void);
static gboolean closeWebViewCb(GtkWidget *window);
GdkPixbuf *create_pixbuf(const gchar *filename);


int main(int argc, char **argv) {

	clock_t start;
	static char home[0x400];
	static char icon[0x400];
	char apath[PATH_MAX];

	system("clear");
	realpath("resources", apath);
	printf(" DEBUG output -----\n");
	printf(" Resources Path: %s\n", apath);

	strcpy(home,"file://");
	strcat(home,apath);
	strcat(home,"/index.html");
	strcpy(icon,apath);
	strcat(icon,"/img/icon.png");


	start = clock();
	largura();
	timeresult(start,"largura");

	start = clock();
	profund();
	timeresult(start,"profund");


	gtk_init(&argc, &argv);

	GtkWidget *mainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	GdkPixbuf *appicon = create_pixbuf(icon);

	gtk_window_set_title(GTK_WINDOW(mainWindow), "Missionarios vs. Canibais");
	gtk_window_set_default_size(GTK_WINDOW(mainWindow), 800, 600);
	gtk_window_set_position(GTK_WINDOW(mainWindow), GTK_WIN_POS_CENTER);
	gtk_window_set_icon(GTK_WINDOW(mainWindow), appicon);

	WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());
	gtk_container_add(GTK_CONTAINER(mainWindow), GTK_WIDGET(webView));

	g_signal_connect(mainWindow, "destroy", G_CALLBACK(destroyWindowCb), NULL);
	g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), mainWindow);

	webkit_web_view_load_uri(webView, home);

	gtk_widget_grab_focus(GTK_WIDGET(webView));
	gtk_widget_show_all(mainWindow);

	g_object_unref(appicon);

	gtk_main();

	return 0;

	int mundiais = 0;
	int palmeiras = mundiais;
	assert(!palmeiras);
}

static void destroyWindowCb(void) {
	gtk_main_quit();
}

static gboolean closeWebViewCb(GtkWidget *window) {
	gtk_widget_destroy(window);
	return true;
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
