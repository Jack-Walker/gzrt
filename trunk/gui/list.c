/***********************************
* File listing tree view generator *
***********************************/
#include <gzrt.h>

static void gen_id ( char * dest, int id, MAINWIN * c )
{
	sprintf( dest, "%04u", id );
}

static void gen_vstart ( char * dest, int id, MAINWIN * c )
{
	sprintf( dest, "0x%08X", U32( &c->z->fs_table[id * 16] ) );
}

static void gen_vend ( char * dest, int id, MAINWIN * c )
{
	sprintf( dest, "0x%08X", U32( &c->z->fs_table[id * 16 + 4] ) );
}

static void gen_name ( char * dest, int id, MAINWIN * c )
{
	if( !c->t )
	{
		strcpy( dest, " " );
		return;
	}
	
	sprintf(dest, "%s", c->t->cur );
	z64nt_read_next( c->t );
}

struct ColumnSpec
{
	char * title;
	void (*func)(char *, int, void *);
}
Cols[] = 
{
	{ "ID",		  gen_id     },
	{ "Filename", gen_name   },
	{ "Start",	  gen_vstart },
	{ "End",	  gen_vend	 }
};

/* Generate the tree view */
GtkWidget * gzrt_wmain_tree_generate ( MAINWIN * c )
{
	GtkWidget    * tv = gtk_tree_view_new();
	GtkListStore    * ls = gtk_list_store_new( sizeof(Cols) / sizeof(struct ColumnSpec), G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, -1 );
	
	/* Create columns */
	for( int i = 0; i < sizeof(Cols) / sizeof(struct ColumnSpec); i++ )
	{
		GtkWidget * r = gtk_cell_renderer_text_new(), * col;
		gtk_tree_view_insert_column_with_attributes( GTK_TREE_VIEW(tv), 
		-1, Cols[i].title, r, "text", i, NULL );
		col = gtk_tree_view_get_column( GTK_TREE_VIEW(tv), i );
		gtk_tree_view_column_set_resizable( col, TRUE );
	}
	
	/* Generate data */
	for( int i = 0; i < z64fs_num_entries( c->z ); i++ )
	{
		GtkTreeIter j;
		
		gtk_list_store_append( GTK_LIST_STORE(ls), &j );
		 
		for( int k = 0; k < sizeof(Cols) / sizeof(struct ColumnSpec); k++ )
		{
			char buffer[64];
			Cols[k].func( buffer, i, c );
			gtk_list_store_set( GTK_LIST_STORE(ls), &j, k, buffer, -1 );
		}
	}
	
	/* Set model */
	gtk_tree_view_set_model( GTK_TREE_VIEW(tv), GTK_TREE_MODEL(ls) );
	
	/* No need */
	g_object_unref( ls );
	
	/* Return it */
	return tv;
}
