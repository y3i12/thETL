#if !defined __KEY_VALUE_IO_INTERFACE_H__
#define __KEY_VALUE_IO_INTERFACE_H__

#include "dioInterface.h"

namespace thetl
{
	class kvioInterface : public dioInterface
	{
	public:
		typedef RecordData							key;
		typedef RecordData*							value;
		typedef std::vector< size_t >				key_index;

		kvioInterface( key_index theKeyIndexes );
		virtual ~kvioInterface( void ) {}

		virtual bool		open( void ) = 0;
		virtual void		close( void ) = 0;
		virtual bool		isOpen( void ) = 0;
		virtual void		flush( void ) = 0;

		virtual bool		seek( int theTarget, dioInterface::SeekDirection theDirection = dioInterface::Current ) = 0;
		virtual bool		find( const RecordData& theKey ) = 0;
		virtual bool		atEnd( void ) const = 0;

		virtual bool		deserialize( RecordData& theOutput ) = 0;
		virtual bool		serialize( const RecordData& theInput ) = 0;

		virtual void		resetCurrentCursor( void ) = 0;
		virtual void		setCurrentCursor( const RecordData& theKey ) = 0;

		virtual void		resetEndCursor( void ) = 0;
		virtual void		setEndCursor( const RecordData& theKey ) = 0;

		void				resetCursors( void );

		kvioInterface::key	makeKey( const RecordData& theInput );

	protected:
		key_index									m_keyIndexes;
	};
}

#endif