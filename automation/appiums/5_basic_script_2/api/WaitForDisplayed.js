import { releaseResource } from '../utils/Func.js';

describe('Learning WebdriverIO API', () => {
   
    after(async () => {
      await releaseResource(driver)
    })

    it('should login successfully', async () => {
      const LOGIN_ICON_HOME_SCREEN = '~Login'
      const SWITCH_BTN='~switch'
      await $(LOGIN_ICON_HOME_SCREEN).then(
        async (ele) => { await ele.click();}
      );

      await $(SWITCH_BTN).then(async (ele) => await ele.waitForDisplayed({timeout: 8000}))
      await $(SWITCH_BTN).then(async (ele) => {
          await ele.click()
      });

      await driver.pause(3000);
    });
});
