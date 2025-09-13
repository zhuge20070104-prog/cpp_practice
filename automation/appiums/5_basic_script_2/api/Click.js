import { releaseResource, addContext, releaseEach } from '../utils/Func.js';


describe('Learning WebdriverIO API', () => {
    after(async function() {
      releaseResource(driver)
    })

    afterEach(async function() {
      releaseEach(this, driver, './screenshot/login.png')
    })

    it('should click on Login Icon successfully', async function () {
        const LOGIN_ICON_HOME_SCREEN = '~Login'
        await $(LOGIN_ICON_HOME_SCREEN).then((ele) => ele.click())
        addContext(this, 'Click on Login button OK')
    });
});
