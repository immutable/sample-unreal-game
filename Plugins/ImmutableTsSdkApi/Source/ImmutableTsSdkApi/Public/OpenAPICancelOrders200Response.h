/**
 * TS SDK API
 * running ts sdk as an api
 *
 * OpenAPI spec version: 1.0.0
 * Contact: contact@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#pragma once

#include "OpenAPIBaseModel.h"
#include "OpenAPICancelOrders200ResponseResult.h"

namespace ImmutableTsSdkApi
{

/*
 * OpenAPICancelOrders200Response
 *
 * Response schema for the cancelOrder endpoint
 */
class IMMUTABLETSSDKAPI_API OpenAPICancelOrders200Response : public Model
{
public:
    virtual ~OpenAPICancelOrders200Response() {}
	bool FromJson(const TSharedPtr<FJsonValue>& JsonValue) final;
	void WriteJson(JsonWriter& Writer) const final;

	TOptional<OpenAPICancelOrders200ResponseResult> Result;
};

}