import { releaseResource, addContext, releaseEach } from '../utils/Func.js';


describe('Learning WebdriverIO API', () => {
    after(async function() {
      releaseResource(driver)
    })

    afterEach(async function() {
      releaseEach(this, driver, './screenshot/login.png')
    })

    it('Swipe Horizontal', async function () {
        const SWIPE_ICON_HOME_SCREEN = '~Swipe'
        const SWIPE_HEADER_TEXT= '//android.widget.TextView[@text="Swipe horizontal"]'

        await $(SWIPE_ICON_HOME_SCREEN).then(async (ele) => await ele.click())
        await $(SWIPE_HEADER_TEXT).then(async (ele) => await ele.click())

        // swipt from right to left 
        const yanchor_percentage = 70
        const xstart_percentage = 90
        const xend_percentage = 10

        let size = await driver.getWindowSize()
        let width = size.width
        let height = size.height
        
        const yanchor = height * yanchor_percentage / 100
        const xstart_point = width * xstart_percentage / 100
        const xend_point = width * xend_percentage / 100

        for(let swipe_time = 0; swipe_time < 5; ++swipe_time) {
          await driver.touchPerform([
            {
              action: 'press',
              options: {
                x: xstart_point,
                y: yanchor
              }
            },
            {
              action: 'wait',
              options: {
                ms: 1000
              }
            },
            {
              action: 'moveTo',
              options: {
                x: xend_point,
                y: yanchor
              }
            },
            {
              action: 'release',
              options: {}
            } 
          ])
          
          driver.pause(1000)
        }

        addContext(this, 'Swipe horizontal OK')

    });
});
