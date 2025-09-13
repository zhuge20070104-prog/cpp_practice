import { releaseResource } from '../utils/Func.js';

describe('Learning WebdriverIO API', () => {
    after(async () => {
      await releaseResource(driver)
    })

    it('should click on Login Icon successfully', async () => {
      const login_item = await $('//android.widget.TextView[@text="Login"]');
      await login_item.click();
    });
});
