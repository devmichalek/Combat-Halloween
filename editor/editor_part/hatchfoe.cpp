#include "hatchfoe.h"
#include "own/file.h"

HatchFoe::HatchFoe( sf::Uint8 w, sf::Uint8 n, float x, float y )
{
	this->w = w;
	this->n = n;
	this->x = x;
	this->y = y;
	
	armour = 0;
	damage = 1;
	velocity = 10;
	heartpoints = 1;
	scale = 0.5;
}

HatchFoe::~HatchFoe()
{
	w = 0;
	n = 0;
	x = 0;
	y = 0;
	
	armour = 0;
	damage = 1;
	velocity = 10;
	heartpoints = 1;
	scale = 0.5;
	
	if( !texts.empty() )
	{
		texts.clear();
	}
}


HatchFoeVisible::HatchFoeVisible()
{
	free();
}

HatchFoeVisible::~HatchFoeVisible()
{
	free();
}

void HatchFoeVisible::free()
{
	table.free();
	infobutton.free();
	plusbutton.free();
	minusbutton.free();
	doublebutton.free();
	
	if( !minimums.empty() )
	{
		minimums.clear();
	}
	
	if( !maximums.empty() )
	{
		maximums.clear();
	}
	
	if( !features.empty() )
	{
		features.clear();
	}
	
	if( !pluspressed.empty() )
	{
		pluspressed.clear();
	}
	
	if( !minuspressed.empty() )
	{
		minuspressed.clear();
	}
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		texts.clear();
	}
	
	if( !formTexts.empty() )
	{
		for( auto &it :formTexts )
		{
			it->free();
			delete it;
			it = NULL;;
		}
		
		formTexts.clear();
	}
	
	// Comment.
	commentState = 0;
	which = 0;
	arrow.free();
	oneOf.free();
	arrowLine = 0;
	arrowCounter = 0;
	addCommentButton.free();
	deleteCommentButton.free();
	nextCommentButton.free();
	backCommentButton.free();
	
	if( !commentsStr.empty() )
	{
		commentsStr.clear();
	}
	
	balloonchat.free();
	
	
	type = -1;
	visible = false;
	wasminus = false;
	
	foe_x = foe_y = 0;
	width = 0;
	height = 0;
}



void HatchFoeVisible::load( float screen_w, float screen_h )
{
	free();
	
	// Sprites.
	table.setIdentity( "hatchFoeVisible-table" );
	infobutton.setIdentity( "hatchFoeVisible-infobutton" );
	plusbutton.setIdentity( "hatchFoeVisible-plusbutton" );
	minusbutton.setIdentity( "hatchFoeVisible-minusbutton" );
	doublebutton.setIdentity( "hatchFoeVisible-doublebutton" );
	
	table.load( "images/menu/table.png" );
	infobutton.load( "images/editor/info.png", 3 );
	plusbutton.load( "images/menu/plus.png", 3 );
	minusbutton.load( "images/menu/minus.png", 3 );
	doublebutton.load( "images/editor/disagree.png", 3 );
	
	table.setScale( 0.25, 0.3 );
	infobutton.setScale( 0.2, 0.2 );
	plusbutton.setScale( 0.4, 0.4 );
	minusbutton.setScale( 0.4, 0.4 );
	doublebutton.setScale( 0.165, 0.165 );
	
	
	// Maximums, minimums.
	minimums.push_back( 0 );
	minimums.push_back( 1 );
	minimums.push_back( 10 );
	minimums.push_back( 1 );
	minimums.push_back( 0.4 );
	
	maximums.push_back( 995 );
	maximums.push_back( 10000 );
	maximums.push_back( 300 );
	maximums.push_back( 1000 );
	maximums.push_back( 1 );
	
	features.push_back( 0 );
	features.push_back( 1 );
	features.push_back( 10 );
	features.push_back( 1 );
	features.push_back( 0.5 );
	
	// Texts.
	for( unsigned i = 0; i < ADD_TEXT; i++ )
	{
		pluspressed.push_back( false );
		minuspressed.push_back( false );
		
		texts.push_back( new MyText() );
		texts[ i ]->setIdentity( "hatchFoeVisible-texts" );
		texts[ i ]->setFont( "fonts/jcandlestickextracond.ttf" );
	}
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		formTexts.push_back( new MyText() );
		formTexts[ i ]->setIdentity( "hatchFoeVisible-formTexts" );
		formTexts[ i ]->setFont( "fonts/jcandlestickextracond.ttf" );
	}
	
	texts[ ARMOUR ]->setText( "0" );
	texts[ DAMAGE ]->setText( "1" );
	texts[ VEL ]->setText( "10" );
	texts[ HP ]->setText( "1" );
	texts[ SCALE ]->setText( "50%" );
	
	formTexts[ ARMOUR ]->setText( "armour: " );
	formTexts[ DAMAGE ]->setText( "damage: " );
	formTexts[ VEL ]->setText( "velocity: " );
	formTexts[ HP ]->setText( "heartpoints: " );
	formTexts[ SCALE ]->setText( "scale: " );
	formTexts[ ADD_TEXT ]->setText( "click to add comment" );
	
	int size = 22;
	for( unsigned i = 0; i < ADD_TEXT; i++ )
	{
		texts[ i ]->setAlpha( 0xFF );
		texts[ i ]->setSize( size );
	}
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		formTexts[ i ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
		formTexts[ i ]->setAlpha( 0xFF );
		formTexts[ i ]->setSize( size );
	}
	
	arrow.setIdentity( "hatchFoeVisible-arrow" );
	arrow.setFont( "fonts/jcandlestickextracond.ttf" );
	arrow.setText( "|" );
	arrow.setAlpha( 0xFF );
	arrow.setColor( sf::Color::Black );
	arrow.setSize( 20 );
	
	oneOf.setIdentity( "hatchFoeVisible-oneOf" );
	oneOf.setFont( "fonts/jcandlestickextracond.ttf" );
	oneOf.setText( "1 of 1" );
	oneOf.setAlpha( 0xFF );
	oneOf.setSize( size );
	
	// Set comment.
	arrowLine = 0.5;	// 0.5 sec.
	
	addCommentButton.setIdentity( "hatchfoe-addCommentButton" );
	addCommentButton.load( "images/menu/plus.png", 3 );
	addCommentButton.setScale( 0.4, 0.4 );
	
	deleteCommentButton.setIdentity( "hatchfoe-deleteCommentButton" );
	deleteCommentButton.load( "images/menu/minus.png", 3 );
	deleteCommentButton.setScale( 0.4, 0.4 );
	
	nextCommentButton.setIdentity( "hatchfoe-nextCommentButton" );
	nextCommentButton.load( "images/level/right.png", 3 );
	nextCommentButton.setScale( 0.2, 0.2 );
	
	backCommentButton.setIdentity( "hatchfoe-backCommentButton" );
	backCommentButton.load( "images/level/left.png", 3 );
	backCommentButton.setScale( 0.2, 0.2 );
	
	balloonchat.load( screen_w, screen_h );
}

void HatchFoeVisible::handle( sf::Event& event )
{
	if( visible )
	{
		if( event.type == sf::Event::MouseButtonReleased )
		{
			infobutton.setOffset( 0 );
			if( commentState == 0 )	doublebutton.setOffset( 0 );
			for( unsigned i = 0; i < pluspressed.size(); i++ )
			{
				pluspressed[ i ] = false;
				minuspressed[ i ] = false;
			}
		}
		
		if( event.type == sf::Event::MouseButtonPressed )
		{
			bool collision = false;
			float mouse_x = event.mouseButton.x;
			float mouse_y = event.mouseButton.y;
			
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				if( commentState == 0 )
				{
					for( unsigned i = 0; i < texts.size(); i++ )
					{
						minusbutton.setPosition( table.getRight(), texts[ i ]->getY() );
						plusbutton.setPosition( minusbutton.getRight(), texts[ i ]->getY() );
						doublebutton.setPosition( plusbutton.getRight(), texts[ i ]->getY() );
						
						if( minusbutton.checkCollision( mouse_x, mouse_y ) )
						{
							collision = true;
							wasminus = true;
							minuspressed[ i ] = true;
							break;
						}
						else if( plusbutton.checkCollision( mouse_x, mouse_y ) )
						{
							collision = true;
							wasminus = false;
							pluspressed[ i ] = true;
							break;
						}
						else if( doublebutton.checkCollision( mouse_x, mouse_y ) && i != SCALE )
						{
							collision = true;
							// printf( "%d\n", i );
							
							if( wasminus )	features[ i ] /= 2;
							else			features[ i ] *= 2;
							
							if( features[ i ] > maximums[ i ] )			features[ i ] = maximums[ i ];
							else if( features[ i ] < minimums[ i ] )	features[ i ] = minimums[ i ];
							
							texts[ i ]->setText( con::itos( static_cast <int> (features[ i ]) ) );
							texts[ i ]->setPosition( formTexts[ HP ]->getRight() +3, formTexts[ i ]->getY() );
							break;
						}
					}
				}
				else
				{
					if( addCommentButton.checkCollision( mouse_x, mouse_y ) )
					{
						collision = true;
						commentsStr.push_back( "" );
						which = commentsStr.size() -1;
						setBalloonChat();
					}
					else if( deleteCommentButton.checkCollision( mouse_x, mouse_y ) )
					{
						collision = true;
						if( commentsStr.size() > 0 )
						{
							commentsStr.erase( commentsStr.begin() +which );
							if( which != 0 )	which --;
							setBalloonChat();
							
							if( commentsStr.empty() )
							{
								doublebutton.setOffset( 0 );
								commentState = 0;
							}
						}
					}
					
					if( commentsStr.size() > 1 )
					{
						if( nextCommentButton.checkCollision( mouse_x, mouse_y ) )
						{
							collision = true;
							if( which < commentsStr.size() -1 )
							{
								which ++;
								setBalloonChat();
							}
						}
						else if( backCommentButton.checkCollision( mouse_x, mouse_y ) )
						{
							collision = true;
							if( which > 0 )
							{
								which --;
								setBalloonChat();
							}
						}
					}
				}
				
				if( infobutton.checkCollision( mouse_x, mouse_y ) )
				{
					collision = true;
					infobutton.setOffset( 1 );
					if( commentState == 1 )
					{
						doublebutton.setOffset( 0 );
						commentState = 0;
						which = 0;
						setUpComments();
					}
					else
					{
						if( commentsStr.empty() )
						{
							commentsStr.push_back( "" );
						}
						
						setBalloonChat();
						setCommentPosition();
						doublebutton.setOffset( 2 );
						commentState = 1;
					}
				}
				
				if( table.checkCollision( mouse_x, mouse_y ) )
				{
					setUpComments();
					collision = true;
					commentState = 0;
					doublebutton.setOffset( 0 );
				}
			}
			
			if( !collision )
			{
				clear();
				commentState = 0;
				doublebutton.setOffset( 0 );
			}
		}
		
		// Writing.
		if( event.type == sf::Event::TextEntered )
		{
			if( commentState == 1 && !commentsStr.empty() )
			{
				int c = event.text.unicode;
				if( c < 126 && c > 31 && c != 92 )
				{
					if( (c == 32 && !commentsStr[ which ].empty()) || c != 32 )
					{
						if( c != '|' && c != '*' )
						{
							commentsStr[ which ] += event.text.unicode;
							setBalloonChat();
							setCommentPosition();
						}
					}
				}
			}
		}
	
		if( event.type == sf::Event::KeyPressed )
		{
			if( event.key.code == sf::Keyboard::Escape )
			{
				if( commentState == 1 )
				{
					setUpComments();
					commentState = 0;
					doublebutton.setOffset( 0 );
				}
				else					clear();
			}
			else if( event.key.code == sf::Keyboard::BackSpace )
			{
				if( commentState == 1 && !commentsStr.empty() )
				{
					if( !commentsStr[ which ].empty() )
					{
						if( commentsStr[ which ].size() > 1 )
						{
							int last = commentsStr[ which ].size() -1;
							if( commentsStr[ which ][ last ] == 'n' )
							{
								if( static_cast <int> (commentsStr[ which ][ last -1 ]) == 92 )
								{
									commentsStr[ which ].pop_back();
									commentsStr[ which ].pop_back();
								}
								else
								{
									commentsStr[ which ].pop_back();
								}
							}
							else
							{
								commentsStr[ which ].pop_back();
							}
						}
						else
						{
							commentsStr[ which ].pop_back();
						}
						
						setBalloonChat();
						setCommentPosition();
					}
				}
			}
			else if( event.key.code == sf::Keyboard::Return )
			{
				if( commentState == 1 )
				{
					if( !commentsStr.empty() )
					{
						if( !commentsStr[ which ].empty() )
						{
							commentsStr[ which ] += "\n";
							setBalloonChat();
							setCommentPosition();
						}
					}
				}
			}
		}
	}
}

void HatchFoeVisible::draw( sf::RenderWindow* &window )
{
	if( visible )
	{
		for( unsigned i = 0; i < pluspressed.size(); i++ )
		{
			if( pluspressed[ i ] )
			{
				if( features[ i ] < maximums[ i ] )
				{
					if( i != SCALE )	features[ i ] += 0.1;
					else
					{
						features[ i ] += 0.001;
					}
						
					
					if( features[ i ] > maximums[ i ] )
					{
						features[ i ] = maximums[ i ];
					}
				}
			}
			else if( minuspressed[ i ] )
			{
				if( features[ i ] > minimums[ i ] )
				{
					if( i != SCALE )	features[ i ] -= 0.1;
					else
					{
						features[ i ] -= 0.001;
					}
					
					if( features[ i ] < minimums[ i ] )
					{
						features[ i ] = minimums[ i ];
					}
				}
			}
			
			if( i != SCALE )
			{
				texts[ i ]->setText( con::itos( static_cast <int> (features[ i ]) ) );
			}
			else
			{
				texts[ i ]->setText( con::itos( features[ i ] *100 ) +"%" );
			}
			
			texts[ i ]->setPosition( formTexts[ HP ]->getRight() +3, formTexts[ i ]->getY() );
		}
		
		window->draw( table.get() );
		window->draw( infobutton.get() );
		
		for( unsigned i = 0; i < formTexts.size(); i++ )
		{
			window->draw( formTexts[ i ]->get() );
		}
		
		for( unsigned i = 0; i < texts.size(); i++ )
		{
			window->draw( texts[ i ]->get() );
			
			minusbutton.setOffset( 0 );
			if( minuspressed[ i ] && commentState == 0 )	minusbutton.setOffset( 1 );
			else if( commentState == 1 )					minusbutton.setOffset( 2 );
			minusbutton.setPosition( table.getRight(), texts[ i ]->getY() );
			window->draw( minusbutton.get() );
			
			plusbutton.setOffset( 0 );
			if( pluspressed[ i ] && commentState == 0 )	plusbutton.setOffset( 1 );
			else if( commentState == 1 )				plusbutton.setOffset( 2 );
			plusbutton.setPosition( minusbutton.getRight(), texts[ i ]->getY() );
			window->draw( plusbutton.get() );
			
			if( i != SCALE )
			{
				doublebutton.setPosition( plusbutton.getRight(), texts[ i ]->getY() );
				window->draw( doublebutton.get() );
			}
		}
	
		if( commentState == 1 )
		{
			window->draw( addCommentButton.get() );
			window->draw( deleteCommentButton.get() );
			if( commentsStr.size() > 1 )
			{
				if( which > 0 )
					window->draw( backCommentButton.get() );
				if( which < commentsStr.size() -1 )
					window->draw( nextCommentButton.get() );
			}
			balloonchat.draw( window );
			
			if( arrowCounter < arrowLine )
				window->draw( arrow.get() );
			
			// Set one of.
			oneOf.setText( con::itos(which +1) +" of " +con::itos(commentsStr.size()) );
			oneOf.setPosition( balloonchat.getLeft() +balloonchat.getWidth()/2 -oneOf.getWidth()/2, balloonchat.getTop() -50 );
			window->draw( oneOf.get() );
		}
	}
}

void HatchFoeVisible::mechanics( double elapsedTime )
{
	if( arrowCounter < arrowLine *2 )
	{
		arrowCounter += elapsedTime;
	}
	else
	{
		arrowCounter = 0;
	}
}



bool& HatchFoeVisible::isVisible()
{
	return visible;
}

void HatchFoeVisible::clear()
{
	visible = false;
}



int HatchFoeVisible::getType()
{
	return type;
}

void HatchFoeVisible::setType( int type )
{
	this->type = type;
}

void HatchFoeVisible::setPosition( float x, float y )
{
	visible = true;
	
	// x = right border of foe
	// y = y of foe
	
	table.setPosition( x, y );
	
	// Setting form texts.
	float border = 3;
	float formTextX = table.getX() +border;
	float formTextY = table.getY() +border;
	
	for( unsigned i = 0; i < texts.size(); i++ )
	{
		formTexts[ i ]->setPosition( formTextX, formTextY +(formTexts[ ARMOUR ]->getHeight() +border)*i );
	}
	
	for( unsigned i = 0; i < texts.size(); i++ )
	{
		texts[ i ]->setPosition( formTexts[ HP ]->getRight() +border, formTexts[ i ]->getY() );
	}
	
	// Buttons.
	formTexts[ ADD_TEXT ]->setPosition( formTextX, table.getBot() -formTexts[ ADD_TEXT ]->getHeight() -border*3 );
	infobutton.setPosition( table.getRight(), formTexts[ ADD_TEXT ]->getY() );
	
	setCommentPosition();
}

void HatchFoeVisible::setFeatures( float a, float d, float v, float h, float s )
{
	features[ ARMOUR ] = a;
	features[ DAMAGE ] = d;
	features[ VEL ] = v;
	features[ HP ] = h;
	features[ SCALE ] = s;
	
	texts[ ARMOUR ]->setText( con::itos( static_cast <int> (a) ) );
	texts[ DAMAGE ]->setText( con::itos( static_cast <int> (d) ) );
	texts[ VEL ]->setText( con::itos( static_cast <int> (v) ) );
	texts[ HP ]->setText( con::itos( static_cast <int> (h) ) );
	texts[ SCALE ]->setText( con::itos( s *100 ) +"%" );
}

void HatchFoeVisible::setComments( vector <string> newComments )
{
	which = 0;
	oneOf.setText( con::itos(which +1) +" of " +con::itos(commentsStr.size()) );
	oneOf.setPosition( balloonchat.getLeft() +balloonchat.getWidth()/2 -oneOf.getWidth()/2, balloonchat.getTop() -50 );
	
	this->commentsStr = newComments;
}

void HatchFoeVisible::setFoeSize( float width, float height )
{
	this->width = width;
	this->height = height;
}

void HatchFoeVisible::setFoePosition( float foe_x, float foe_y )
{
	this->foe_x = foe_x;
	this->foe_y = foe_y;
}



float HatchFoeVisible::getArmour()
{
	return features[ ARMOUR ];
}

float HatchFoeVisible::getDamage()
{
	return features[ DAMAGE ];
}

float HatchFoeVisible::getVelocity()
{
	return features[ VEL ];
}

float HatchFoeVisible::getHeartpoints()
{
	return features[ HP ];
}

float HatchFoeVisible::getScale()
{
	return features[ SCALE ];
}

float HatchFoeVisible::getX()
{
	float absoluteX = foe_x -width *features[ SCALE ] /2;
	
	return absoluteX;
}

float HatchFoeVisible::getY()
{
	float absoluteY = foe_y -height *features[ SCALE ];
	
	return absoluteY;
}

vector <string> HatchFoeVisible::getComments()
{
	setUpComments();
	
	return commentsStr;
}



void HatchFoeVisible::setUpComments()
{
	for( unsigned i = 0; i < commentsStr.size(); i++ )
	{
		deleteSpaces( commentsStr[ i ] );
		if( commentsStr[ i ] == "" )
		{
			commentsStr.erase( commentsStr.begin() +i );
			i --;
		}
	}
}

void HatchFoeVisible::setBalloonChat()
{
	if( commentsStr[ which ] != "" )
	{
		balloonchat.setText( commentsStr[ which ] );
	}
	else
	{
		balloonchat.setText( "Start typing..." );
	}
}

void HatchFoeVisible::setCommentPosition()
{
	// Set arrow position, looking for x.
	if( !commentsStr.empty() )
	{
		balloonchat.setPosition( doublebutton.getRight() +doublebutton.getWidth() *3, table.getBot() );
		float y = balloonchat.getBot() -arrow.getHeight() +2;
		if( commentsStr[ which ].empty() )
		{
			arrow.setPosition( balloonchat.getRight(), y );
		}
		else
		{
			string tempStr = "";
			for( int i = commentsStr[ which ].size() -1; i >= 0; i-- )
			{
				if( i > 0 )
				{
					if( commentsStr[ which ][ i ] == '\n' )
					{
						break;
					}
				}
				
				tempStr += commentsStr[ which ][ i ];
			}
			if( tempStr.empty() )	tempStr = " ";
			// printf( "1.%s\n2.%s\n", commentsStr[ which ].c_str(), tempStr.c_str() );
			balloonchat.setText( tempStr );
			arrow.setPosition( balloonchat.getRight(), y );
			setBalloonChat();
		}
	}
	
	balloonchat.setPosition( doublebutton.getRight() +doublebutton.getWidth() *3, table.getBot() );
	deleteCommentButton.setPosition( balloonchat.getLeft() +balloonchat.getWidth()/2 -addCommentButton.getWidth(), balloonchat.getBot() +doublebutton.getHeight() +3 );
	addCommentButton.setPosition( balloonchat.getLeft() +balloonchat.getWidth()/2, balloonchat.getBot() +doublebutton.getHeight() +3 );
	backCommentButton.setPosition( balloonchat.getLeft() -doublebutton.getWidth()*2, balloonchat.getTop() -doublebutton.getHeight()*2 );
	nextCommentButton.setPosition( balloonchat.getRight() +doublebutton.getWidth() -2, balloonchat.getTop() -doublebutton.getHeight()*2 );
}

void HatchFoeVisible::deleteSpaces( string &line )
{
	// Delete spaces.
	for( unsigned i = 0; i < line.size(); i++ )
	{
		if( line[ i ] == ' ' )
		{
			line.erase( i, 1 );
			i --;
		}
		else
		{
			break;
		}
	}
	
	if( !line.empty() )
	{
		for( int i = line.size() -1; i >= 0 ; i-- )
		{
			if( line[ i ] == ' ' )
			{
				line.erase( i, 1 );
			}
			else
			{
				break;
			}
		}
	}
}