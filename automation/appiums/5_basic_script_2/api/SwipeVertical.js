import { releaseResource } from '../utils/Func.js';

describe('Learning WebdriverIO API', () => {
   
    after(async () => {
      await releaseResource(driver)
    })

    it('Swipe Vertical', async () => {
      const FORMS_ICON_HOME_SCREEN = '~Forms'
      const ACTIVE_BUTTON = '~button-Active'
      const FORM_HEADER_TEXT = '//android.widget.TextView[@text="Form components"]'

      await $(FORMS_ICON_HOME_SCREEN).then(
        async (ele) => { await ele.click();}
      );


      const size = await driver.getWindowSize()
      const width = size.width
      const height = size.height
      const xanchor_percentage = 50
      const ystart_point_percentage = 90
      const yend_point_percentage = 10

      const xanchor = width * xanchor_percentage /100
      const ystart_point = height * ystart_point_percentage /100
      const yend_point = height * yend_point_percentage /100

      await $(FORM_HEADER_TEXT).then(async ele => await ele.click())

      await driver.touchPerform([
        {
            action: 'press',
            options: {
                x: xanchor,
                y: ystart_point
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
                x: xanchor,
                y: yend_point
            }
        },
        {
            action: 'release',
            options: {}
        }
      ])

      await $(ACTIVE_BUTTON).then(async (ele) => ele.click())
      await driver.pause(3000);
    });
});
