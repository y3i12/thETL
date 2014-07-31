#if !defined __FILE_IO_RECORD_STATE_MACHINE_H__
#define __FILE_IO_RECORD_STATE_MACHINE_H__

#include "RecordDescription.h"
#include "RecordData.h"
#include "fioRecordIdentification.h"

#include <map>
#include <list>

namespace thetl
{
    // TODO: fazer templatização e continuar com trabalho da maquina de estados
    template < class T >
	class fioRecordStateMachine
	{
	public:
		class State
		{
			friend class fioRecordStateMachine< T >;
		public:
			State( State* theParentState, const T& theId, size_t theIdPosition, RecordDescription* theRecordDescription );
			State( State* theParentState, RecordDescription* theRecordDescription );

			~State( void );

		private:
			bool getDescription( const T& theInput, RecordDescription*& theOutput );

		private:
			typename fioRecordStateMachine< typename T >::State*                                    m_parentState;
			RecordDescription*                                                                      m_recordDescription;
			riInterface< T >*                                                                       m_identification;
			std::list< typename fioRecordStateMachine< T >::State* >                                m_nextStates;
			typename std::list< typename fioRecordStateMachine< typename T >::State* >::iterator    m_nextState;
		};

		fioRecordStateMachine( void );

		bool getDescription( const T& theInput, RecordDescription*& theOutput );

		State* addParseState( const T& theId, size_t theIdPosition, RecordDescription*& theRecordDescription, State* theParentState );
		State* rootState( void ) { return &m_rootState; }

	private:
		State   m_rootState;
		State*  m_currentState;
	};

	template < class T >
	fioRecordStateMachine< T >::State::State( typename fioRecordStateMachine< T >::State* theParentState, const T& theId, size_t theIdPosition, RecordDescription* theRecordDescription ) :
		m_parentState( theParentState ),
		m_recordDescription( theRecordDescription ),
		m_identification( new PatternRecord< T >( theId, theIdPosition ) )
	{
		m_parentState.m_nextStates.push_back( this )
	}

	template < class T >
	fioRecordStateMachine< T >::State::State( typename fioRecordStateMachine< T >::State* theParentState, RecordDescription* theRecordDescription ) :
		m_parentState( theParentState ),
		m_recordDescription( theRecordDescription ),
		m_identification( new SingleRecord< T >( ) )
	{
		m_parentState.m_nextStates.push_back( this )
	}

	template < class T >
	fioRecordStateMachine< T >::State::~State( void )
	{
		delete m_recordDescription;
		delete m_identification;
	}

	template < class T >
	bool fioRecordStateMachine< T >::State::getDescription( const T& theInput, RecordDescription*& theOutput, typename fioRecordStateMachine< T >::State*& theOutputState )
	{
		for ( ; m_nextState != m_nextStates.end( ); ++m_nextState )
		{
		    if ( m_identification->fitsInRecord( theInput )
		    {
			    theOutput       = m_recordDescription;
				theOutputState  = this;
			    return true;
		    }
		}
		return false;
	}

	template < class T >
	fioRecordStateMachine< T >::fioRecordStateMachine( void ) :
		m_rootState( 0, 0 ),
		m_currentState( &m_rootState )
    { 
    }


	template < class T >
	bool fioRecordStateMachine< T >::getDescription( const T& theInput, RecordDescription*& theOutput )
	{
		return true;
	}

	template < class T >
	typename fioRecordStateMachine< T >::State* fioRecordStateMachine< T >::addParseState( const T& theId, size_t theIdPosition, RecordDescription*& theRecordDescription, typename fioRecordStateMachine< T >::State* theParentState )
	{
		new State( theParentState ? theParentState : &m_rootState, theId, theIdPosition, theRecordDescription );
	}
}

#endif