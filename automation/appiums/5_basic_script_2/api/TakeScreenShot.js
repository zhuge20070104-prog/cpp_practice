import { releaseResource } from '../utils/Func.js';

describe('Learning WebdriverIO API', () => {
  
    after(async () => {
      await releaseResource(driver)
    })

    it('should login successfully', async () => {
      const FORM_ICON_HOME_SCREEN = '~Forms'
      const SWITCH_BTN='~switch'

      await $(FORM_ICON_HOME_SCREEN).then(
        async (ele) => {await ele.click();}
      );
    
      await $(SWITCH_BTN).then(async (ele) => {
          await ele.waitForDisplayed()
      })

      await driver.saveScreenshot("./screenshot/whole.png");

      await $(SWITCH_BTN).then(async (ele)=>{
          await ele.click()
      });

      await $(SWITCH_BTN).then(async (ele) => {
          await ele.saveScreenshot("./screenshot/switch_button.png")
      });
      
      await driver.pause(3000);
    });
});
