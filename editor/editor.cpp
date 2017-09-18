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
	play = false;
	
	background.free();
	editor_buttons.free();
	editor_information.free();
	editor_details.free();
	editor_options.free();
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
	
	// Set editor buttons.
	editor_buttons.load( screen_w, screen_h );
	
	// Set editor information.
	editor_information.load( screen_w, screen_h );
	
	// Set editor details.
	editor_details.load( screen_w, screen_h );
	
	// Set editor options.
	editor_options.load( screen_w, screen_h );
	
	// Set tiles editor.
	tiles_editor.load( screen_w, screen_h );
	
	// Set chat.
	chat.load( screen_w, screen_h, 1 );
	chat.setCommandColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	chat.setTypicalColor( sf::Color( 0xBA, 0xBA, 0xBA ) );
}

void Editor::handle( sf::Event& event )
{
	if( !back && !play )
	{
		if( editor_details.getNameStatus() == 0 && editor_options.getStatus() == 0 )
		{
			chat.handle( event );
		}
		
		if( !chat.isOpen() )
		{
			if( editor_details.getNameStatus() == 0 )
			{
				editor_options.handle( event );
				
				if( editor_options.getStatus() == 0 )
				{
					editor_information.handle( event );
			
					if( !editor_information.isActive() )
					{
						tiles_editor.setAdditionalX( editor_details.getAdditionalX() );
						tiles_editor.setAdditionalY( editor_details.getAdditionalY() );
						tiles_editor.handle( event );
						editor_buttons.handle( event );
					}
				}
			}
			
			if( !editor_information.isActive() && editor_options.getStatus() == 0 )
			{
				editor_details.handle( event );
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
	
	tiles_editor.setAdditionalX( editor_details.getAdditionalX() );
	tiles_editor.setAdditionalY( editor_details.getAdditionalY() );
	tiles_editor.draw( window );
	
	editor_buttons.draw( window );
	
	editor_details.setGrid( tiles_editor.getGrid() );
	editor_details.setType( tiles_editor.getType() );
	editor_details.setChosen( tiles_editor.getChosen() );
	editor_details.draw( window );
	
	editor_information.drawLayout( window, editor_details.getNameStatus() || editor_buttons.isOptions() );
	editor_information.draw( window );
	editor_details.drawName( window );
	editor_options.draw( window );
	
	chat.draw( window );
}

void Editor::mechanics( double elapsedTime )
{
	if( !back && !play )
	{
		chat.mechanics( elapsedTime );
		if( chat.isCommand() )
		{
			// Editor buttons.
			if( chat.findCommand( "@menu" ) || chat.findCommand( "@back" ) )
			{
				editor_buttons.setHome();
			}
			else if( chat.findCommand( "@options" ) || chat.findCommand( "@settings" ) || chat.findCommand( "@sets" ) )
			{
				editor_buttons.setOptions();
				chat.isOpen() = false;
			}
			else if( chat.findCommand( "@name" ) || chat.findCommand( "@title" ) )
			{
				editor_buttons.setName();
				chat.isOpen() = false;
			}
			else if( chat.findCommand( "@rubbish" ) || chat.findCommand( "@erase" ) ||
			chat.findCommand( "@delete" ) || chat.findCommand( "@remove" ) ||
			chat.findCommand( "@cut" ) || chat.findCommand( "@excise" ) )
			{
				editor_buttons.setDelete();
			}
			else if( chat.findCommand( "@save" ) )
			{
				editor_buttons.setSave();
			}
			else if( chat.findCommand( "@load" ) )
			{
				editor_buttons.setLoad();
			}
			else if( chat.findCommand( "@play" ) || chat.findCommand( "@start" ) )
			{
				editor_buttons.setPlay();
			}
			else if( chat.findCommand( "@upload" ) )
			{
				editor_buttons.setUpload();
			}
			
			// Tiles editor.
			else if( chat.findCommand( "@clear" ) )
			{
				tiles_editor.clearVector();
			}
			
			// Information settings.
			else if( chat.findCommand( "@yes" ) )
			{
				if( editor_information.isActive() )
				{
					editor_information.setStatus( 2 );
				}
			}
			else if( chat.findCommand( "@no" ) )
			{
				if( editor_information.isActive() )
				{
					editor_information.setStatus( 3 );
				}
			}
			// Command doesn't exist.
			else
			{
				chat.setError();
			}
		}
		
		tiles_editor.setRubbish( editor_buttons.isDelete() );
		
		if( !editor_information.isActive() )
		{
			if( editor_buttons.isAnything() )
			{
				if( editor_buttons.getInfo() != " " )
				{
					editor_information.setInfo( editor_buttons.getInfo() );
					editor_information.setWorldname( editor_buttons.getWorldname( editor_details.getName() ) );
					editor_information.setAsVisible();
				}
			}
		}
		
		if( editor_buttons.isOptions() )	// Show options.
		{
			if( editor_options.getStatus() == 0 )
			{
				editor_options.setStatus( 1 );
			}
		}
		else if( editor_buttons.isName() )	// Name.
		{
			if( editor_details.getNameStatus() == 0 )
			{
				editor_details.setNameStatus( 1 );
			}
		}
		else if( editor_buttons.isDelete() )	// Delete mode.
		{
			tiles_editor.reset();
		}
		
		// Reset by action.
		if( editor_options.getStatus() == 2 )
		{
			editor_buttons.reset();
			editor_options.setStatus( 0 );
		}
		else if( editor_details.getNameStatus() == 2 )
		{
			editor_buttons.reset();
			editor_details.setNameStatus( 0 );
		}
		
		// Answers.
		if( editor_information.answerYes() )
		{
			if( editor_buttons.isHome() )	// Back to menu.
			{
				back = true;
				chat.isOpen() = false;
			}
			else if( editor_buttons.isSave() )	// Save.
			{
				tiles_editor.save( editor_details.getName() );
			}
			else if( editor_buttons.isLoad() )	// Load.
			{
				tiles_editor.load( editor_details.getName() );
			}
			else if( editor_buttons.isPlay() )	// Test playing.
			{
				play = true;
				chat.isOpen() = false;
			}
			else if( editor_buttons.isUpload() )	// Upload world.
			{
				
			}
		}
		else if( editor_information.answerNo() )
		{
			editor_buttons.reset();
		}
		
		editor_details.mechanics( elapsedTime );
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
		back = false;
		editor_buttons.reset();
		tiles_editor.reset();
		editor_details.setGrid( tiles_editor.getGrid() );
		editor_details.setType( tiles_editor.getType() );
		editor_details.setChosen( tiles_editor.getChosen() );
		chat.reset();
		return true;
	}
	
	return false;
}

bool Editor::isPlay()
{
	if( play )
	{
		play = false;
		editor_buttons.reset();
		tiles_editor.reset();
		editor_details.setGrid( tiles_editor.getGrid() );
		editor_details.setType( tiles_editor.getType() );
		editor_details.setChosen( tiles_editor.getChosen() );
		chat.reset();
		return true;
	}
	
	return false;
}