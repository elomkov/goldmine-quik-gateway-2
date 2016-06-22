/*
 * currentparametertableparser.h
 */

#ifndef TABLES_CURRENTPARAMETERTABLEPARSER_H_
#define TABLES_CURRENTPARAMETERTABLEPARSER_H_

#include "core/tables/datasink.h"
#include "core/tables/tableparser.h"
#include "core/tables/tableparserfactoryregistry.h"

#include <unordered_map>
#include <memory>

class CurrentParameterTableParser : public TableParser
{
public:
	typedef std::shared_ptr<CurrentParameterTableParser> Ptr;

	CurrentParameterTableParser(const std::string& topic, const DataSink::Ptr& datasink);
	virtual ~CurrentParameterTableParser();

	virtual bool acceptsTopic(const std::string& topic);
	virtual void incomingTable(const XlTable::Ptr& table);

	virtual void parseConfig(const Json::Value& root);

private:
	bool schemaObtained() const;
	void obtainSchema(const XlTable::Ptr& table);

	void parseRow(int row, const XlTable::Ptr& table);

private:
	std::string m_topic;
	std::unordered_map<std::string, unsigned long> m_volumes;
	std::unordered_map<std::string, double> m_prices;
	std::unordered_map<std::string, double> m_bids;
	std::unordered_map<std::string, double> m_asks;

	std::vector<int> m_schema;

	DataSink::Ptr m_datasink;
};

class CurrentParameterTableParserFactory : public TableParserFactory
{
public:
	virtual TableParser::Ptr create(const std::string& topic, const DataSink::Ptr& datasink) override;
};

#endif /* TABLES_CURRENTPARAMETERTABLEPARSER_H_ */
