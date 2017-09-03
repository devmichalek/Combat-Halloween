#include "editor.h"

Editor::Editor()
{
	free();
}

Editor::~Editor()
{
	free();
}

void Editor::free()
{
	back = false;
	
	background.free();
	menubutton.free();
	rubbishbutton.free();
	editor_buttons.free();
	tiles_editor.free();
	chat.free();
}

void Editor::load( float screen_w, float screen_h )
{
	free();
	
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	// Background.
	background.setIdentity( "editor-background" );
	background.load( "images/play/background.png" );
	background.setScale( scale_x, scale_y );
	
	// Circle buttons.
	menubutton.load( "images/level/home.png" );
	menubutton.setPosition( 0, 0, scale_x, scale_y );
	menubutton.setPosition( screen_w /256 +menubutton.getWidth(), screen_h /144 +menubutton.getHeight(), scale_x, scale_y );
	rubbishbutton.load( "images/play/rubbish.png" );
	rubbishbutton.setPosition( screen_w -(menubutton.getWidth() +screen_w /170)*2, screen_h /144 +menubutton.getHeight(), scale_x, scale_y );
	
	// Set editor buttons.
	editor_buttons.load( screen_w, screen_h );
	
	// Set tiles editor.
	tiles_editor.load( screen_w, screen_h );
	
	// Set chat.
	chat.load( screen_w, screen_h );
	chat.setBlack();
}

void Editor::handle( sf::Event& event )
{
	if( !back )
	{
		chat.handle( event );
		
		if( !chat.isOpen() )
		{
			menubutton.handle( event );
			rubbishbutton.handle( event );
			editor_buttons.handle( event );
			
			if( !editor_buttons.isFocus() )
			{
				tiles_editor.handle( event, rubbishbutton.isActive()  );
			}
		}
	}
}

void Editor::head( sf::RenderWindow* &window, double elapsedTime )
{
	draw( window );
	mechanics( elapsedTime );
}



void Editor::draw( sf::RenderWindow* &window )
{
	window->draw( background.get() );
	menubutton.draw( window );
	rubbishbutton.draw( window );
	editor_buttons.draw( window );
	
	if( !editor_buttons.isFocus() )
	{
		tiles_editor.draw( window );
	}
	chat.draw( window );
}

void Editor::mechanics( double elapsedTime )
{
	if( !back )
	{
		chat.mechanics( elapsedTime );
		if( chat.isUsed() )
		{
			// Someone clicked backtomenu button.
			if( chat.getCommand( "@menu" ) || chat.getCommand( "@back" ) ||
			chat.getCommand( "@aback" ) || chat.getCommand( "@return" ) )
			{
				menubutton.setChanged( true );
			}
			
			// Rubbish button.
			else if( chat.getCommand( "@rubbish" ) || chat.getCommand( "@erase" ) ||
			chat.getCommand( "@delete" ) || chat.getCommand( "@remove" ) ||
			chat.getCommand( "@cut" ) || chat.getCommand( "@excise" ) )
			{
				rubbishbutton.setActive( !rubbishbutton.isActive() );
				rubbishbutton.setChanged( !rubbishbutton.isActive() );
			}
			
			// Editor buttons.
			else if( chat.getCommand( "@load" ) )
			{
				editor_buttons.setLoad();
			}
			else if( chat.getCommand( "@save" ) )
			{
				editor_buttons.setSave();
			}
			else if( chat.getCommand( "@focus turn" ) || chat.getCommand( "@focus" ) )
			{
				editor_buttons.setFocus( !editor_buttons.isFocus() );
			}
			else if( chat.getCommand( "@focus on" ) )
			{
				editor_buttons.setFocus( true );
			}
			else if( chat.getCommand( "@focus off" ) )
			{
				editor_buttons.setFocus( false );
			}
			
			// Tiles editor.
			else if( chat.getCommand( "@clear" ) )
			{
				tiles_editor.clearVector();
			}
		}
		
		
		// Back to menu.
		if( menubutton.isChanged() )
		{
			chat.isOpen() = false;
			back = true;
		}
		
		if( rubbishbutton.isChanged() )
		{
			tiles_editor.resetChosen();
		}
		
		// Save / Load.
		if( editor_buttons.isSave() )
		{
			tiles_editor.save( editor_buttons.getPath() );
		}
		else if( editor_buttons.isLoad() )
		{
			tiles_editor.load( editor_buttons.getPath() );
		}
	}
}



void Editor::setUsername( string line )
{
	chat.setUsername( line );
}



bool Editor::isBack()
{
	if( back )
	{
		menubutton.setActive( false );
		editor_buttons.reset();
		tiles_editor.resetChosen();
		chat.reset();
		back = false;
		return true;
	}
	
	return false;
}
