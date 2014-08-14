#include "map_test.h"


#include "MapKeyValueIO.h"

#include "CSVFileIO.h"
#include "dfsFStream.h"
#include "RecordData.h"
#include <chrono>


void map_test( void )
{
	thetl::RecordDescription theRecordDescription;
	thetl::CSVFileIO theCSVFileIO( std::ios_base::in, &theRecordDescription, ',', true );

	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 00 - Year					1987
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 01 - Month					10
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 02 - DayofMonth				14
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 03 - DayOfWeek				3
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 04 - DepTime					741
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 05 - CRSDepTime				730
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 06 - ArrTime					912
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 07 - CRSArrTime				849
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 08 - UniqueCarrier			PS
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 09 - FlightNum				1451
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 10 - TailNum					NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 11 - ActualElapsedTime		91
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 12 - CRSElapsedTime			79
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 13 - AirTime					NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 14 - ArrDelay				23
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 15 - DepDelay				11
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 16 - Origin					SAN
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 17 - Dest					SFO
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 18 - Distance				447
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 19 - TaxiIn					NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 20 - TaxiOut					NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 21 - Cancelled				0
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 22 - CancellationCode		NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// 23 - Diverted				0
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 24 - CarrierDelay			NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 25 - WeatherDelay			NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 26 - NASDelay				NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 27 - SecurityDelay			NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// 28 - LateAircraftDelay		NA

	theCSVFileIO.sourceString( "../data_set/1987.csv" );
	theCSVFileIO.open( );

	thetl::RecordData theRecordData;
	size_t n = 0;

	// key: Origin, Dest
	thetl::MultiMapKeyValueIO theKeyMapIO( { 16, 17 } );

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now( );

	while ( !theCSVFileIO.atEnd( ) )
	{
		theCSVFileIO.deserialize( theRecordData );
		theKeyMapIO.serialize( theRecordData );

		++n;
		if ( !( n % 100000 ) )
		{
			std::cout << n << " lines extracted..." << std::endl;
#if defined _DEBUG
			break;
#endif
		}
	}

	std::chrono::duration< double > time_span = std::chrono::duration_cast< std::chrono::duration< double > >( std::chrono::high_resolution_clock::now( ) - t1 );

	std::cout << "It took me " << time_span.count( ) << " seconds, total of " << ( static_cast< double >( n ) / time_span.count( ) ) << " lines/sec" << std::endl;

	theCSVFileIO.close( );

	std::cout << "Creating output flights from SFO to LAS" << std::endl;
	theKeyMapIO.setCurrentCursor( thetl::RecordData( { "SFO", "LAS" } ) );
	theKeyMapIO.setEndCursor( thetl::RecordData( { "SFO", "LAS" } ) );

	thetl::CSVFileIO SFO_LAS_output( std::ios_base::out, &theRecordDescription, ',', true );

	SFO_LAS_output.sourceString( "../data_set/SFO_LAS.csv" );
	SFO_LAS_output.open( );

	n = 0;
	while ( !theKeyMapIO.atEnd( ) )
	{
		++n;
		theKeyMapIO.deserialize( theRecordData );
		SFO_LAS_output.serialize( theRecordData );
	}

	SFO_LAS_output.close( );

	std::cout << "Done the output of " << n << " lines ;-)" << std::endl;
}