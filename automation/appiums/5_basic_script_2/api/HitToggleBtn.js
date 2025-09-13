import { releaseResource } from '../utils/Func.js';

describe('Learning WebdriverIO API', () => {
    
    after(async () => {
      await releaseResource(driver)
    })

    it('should login successfully', async () => {
      const FORM_ICON_HOME_SCREEN = '~Forms'
      const SWITCH_BTN='~switch'
      await $(FORM_ICON_HOME_SCREEN).then(
        (ele) => ele.click()
      );

      await $(SWITCH_BTN).then(ele => 
          ele.waitForDisplayed({timeout: 6000}))
    
      await $(SWITCH_BTN).then((ele)=>{
          ele.click()
      });

      await driver.pause(3000);
    });
});
