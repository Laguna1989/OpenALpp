#include <catch2/catch.hpp>
#include <oalpp/common/audio_exceptions.hpp>

TEST_CASE("AudioException returns correct message on what", "[Audio Exception]")
{

    std::string const message { "my custom message" };
    oalpp::AudioException exception { message };

    REQUIRE(message == exception.what());
}

TEST_CASE("AudioSystemException returns correct message on what", "[Audio Exception]")
{
    std::string const message { "my custom message" };
    oalpp::AudioSystemException exception { message };

    REQUIRE(message == exception.what());
}
