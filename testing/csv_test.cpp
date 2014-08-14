#include <iostream>
#include "CSVFileIO.h"
#include "dfsFStream.h"
#include "RecordData.h"
#include <chrono>


void csv_test( void )
{
	thetl::RecordDescription theRecordDescription;
	thetl::CSVFileIO theCSVFileIO( std::ios_base::in, &theRecordDescription, ',', true );

	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// Year						1987
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// Month					10
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// DayofMonth				14
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// DayOfWeek				3
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// DepTime					741
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// CRSDepTime				730
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// ArrTime					912
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// CRSArrTime				849
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// UniqueCarrier			PS
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// FlightNum				1451
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// TailNum					NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// ActualElapsedTime		91
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// CRSElapsedTime			79
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// AirTime					NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// ArrDelay					23
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// DepDelay					11
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// Origin					SAN
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// Dest						SFO
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// Distance					447
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// TaxiIn					NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// TaxiOut					NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// Cancelled				0
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// CancellationCode			NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::Integer ) );	// Diverted					0
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// CarrierDelay				NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// WeatherDelay				NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// NASDelay					NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// SecurityDelay			NA
	theRecordDescription.push_back( new thetl::dfsFStream( thetl::DataField::String ) );	// LateAircraftDelay		NA

	theCSVFileIO.sourceString( "../data_set/1987.csv" );
	theCSVFileIO.open( );

	thetl::RecordData theRecordData;
	size_t n = 0;

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now( );

	while ( !theCSVFileIO.atEnd( ) )
	{
		theCSVFileIO.deserialize( theRecordData );
		++n;
		if ( !( n % 100000 ) )
		{
			std::cout << n << " lines extracted..." << std::endl;
		}
	}

	std::chrono::duration< double > time_span = std::chrono::duration_cast< std::chrono::duration< double > >( std::chrono::high_resolution_clock::now( ) - t1 );

	std::cout << "It took me " << time_span.count( ) << " seconds, total of " << ( static_cast< double >( n ) / time_span.count( ) ) << " lines/sec" << std::endl;
}