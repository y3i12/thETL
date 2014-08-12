#include "kvioInterface.h"

using namespace thetl;

kvioInterface::kvioInterface( kvioInterface::key_index theKeyIndexes ) :
	m_keyIndexes( theKeyIndexes )
{

}

void kvioInterface::resetCursors( void ) 
{ 
	resetCurrentCursor( ); 
	resetEndCursor( ); 
}


kvioInterface::key kvioInterface::makeKey( const RecordData& theInput )
{
	kvioInterface::key theOutput;

	for ( auto idx : m_keyIndexes )
	{
		theOutput.push_back( theInput[ idx ] );
	}
	return theOutput;
}