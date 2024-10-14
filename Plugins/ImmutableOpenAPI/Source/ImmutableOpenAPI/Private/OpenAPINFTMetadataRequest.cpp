/**
 * Immutable zkEVM API
 * Immutable Multi Rollup API
 *
 * OpenAPI spec version: 1.0.0
 * Contact: support@immutable.com
 *
 * NOTE: This class is auto generated by OpenAPI Generator
 * https://github.com/OpenAPITools/openapi-generator
 * Do not edit the class manually.
 */

#include "OpenAPINFTMetadataRequest.h"

#include "ImmutableOpenAPIModule.h"
#include "OpenAPIHelpers.h"

#include "Templates/SharedPointer.h"

namespace ImmutableOpenAPI
{

void OpenAPINFTMetadataRequest::WriteJson(JsonWriter& Writer) const
{
	Writer->WriteObjectStart();
	if (Name.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("name")); WriteJsonValue(Writer, Name.GetValue());
	}
	if (Description.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("description")); WriteJsonValue(Writer, Description.GetValue());
	}
	if (Image.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("image")); WriteJsonValue(Writer, Image.GetValue());
	}
	if (ExternalUrl.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("external_url")); WriteJsonValue(Writer, ExternalUrl.GetValue());
	}
	if (AnimationUrl.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("animation_url")); WriteJsonValue(Writer, AnimationUrl.GetValue());
	}
	if (YoutubeUrl.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("youtube_url")); WriteJsonValue(Writer, YoutubeUrl.GetValue());
	}
	if (Attributes.IsSet())
	{
		Writer->WriteIdentifierPrefix(TEXT("attributes")); WriteJsonValue(Writer, Attributes.GetValue());
	}
	Writer->WriteObjectEnd();
}

bool OpenAPINFTMetadataRequest::FromJson(const TSharedPtr<FJsonValue>& JsonValue)
{
	const TSharedPtr<FJsonObject>* Object;
	if (!JsonValue->TryGetObject(Object))
		return false;

	bool ParseSuccess = true;

	ParseSuccess &= TryGetJsonValue(*Object, TEXT("name"), Name);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("description"), Description);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("image"), Image);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("external_url"), ExternalUrl);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("animation_url"), AnimationUrl);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("youtube_url"), YoutubeUrl);
	ParseSuccess &= TryGetJsonValue(*Object, TEXT("attributes"), Attributes);

	return ParseSuccess;
}

}
