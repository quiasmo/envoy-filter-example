#include "test/integration/integration.h"
#include "test/integration/utility.h"

namespace Envoy {
class S4NIntegrationTest : public BaseIntegrationTest,
                             public testing::TestWithParam<Network::Address::IpVersion> {
public:
  S4NIntegrationTest() : BaseIntegrationTest(GetParam()) {}
  /**
   * Initializer for an individual integration test.
   */
  void SetUp() override {
    createTestServer("s4n_server.json", {"S4N_port"});
  }

  /**
   * Destructor for an individual integration test.
   */
  void TearDown() override {
    test_server_.reset();
  }
};

INSTANTIATE_TEST_CASE_P(IpVersions, S4NIntegrationTest,
                        testing::ValuesIn(TestEnvironment::getIpVersionsForTest()));

TEST_P(S4NIntegrationTest, S4N) {
  Buffer::OwnedImpl buffer("hello");
  std::string response;
  RawConnectionDriver connection(lookupPort("S4N_port"), buffer,
                                 [&](Network::ClientConnection&, const Buffer::Instance& data)
                                     -> void {
                                       response.append(TestUtility::bufferToString(data));
                                       connection.close();
                                     }, GetParam());

  connection.run();
  EXPECT_EQ("hello", response);
}
} // Envoy
