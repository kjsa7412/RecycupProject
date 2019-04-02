package com.example.marsm_000.recycupproject;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.animation.AnimationUtils;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.ViewFlipper;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

public class MainActivity2 extends Activity implements View.OnTouchListener {

    ImageButton powerButton;
   // TextView powerText;
    ImageView powerText;
    ImageView RSlideImageButton;
    ImageView LSlideImageButton;
    ImageView left1;
    ImageView leftText1;
    ImageView left2;
    ImageView leftText2;
    ImageView left3;
    ImageView leftText3;
    ImageView left4;
    ImageView leftText4;
    ImageView right1;
    ImageView rightText1;
    ImageView right2;
    ImageView rightText2;
    ImageView right3;
    ImageView rightText3;
    ImageView right4;
    ImageView rightText4;
    ImageView stateLine;
    ImageView totalPer;
    ImageView RefreshButton;



    /** ViewFlipper 컴포넌트 객체 */
    private ViewFlipper m_viewFlipper;
    /** ViewFilpper 안에서 터치된 X축의 좌표값 */
    private int m_nPreTouchPosX = 0;
    private int checkimg = 1;
    private boolean isNextForceHidden;
    private boolean isDoneForceHidden;
    private int onoff;
    private int R_1 = 2;
    private int R_2 = 3;
    private int R_3 = 4;
    private int R_4 = 6;
    private int L_1 = 8;
    private int L_2 = 2;
    private int L_3 = 3;
    private int L_4 = 8;
    private int sumValue = 0;

    private String test;
    private URLConnector task;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        m_viewFlipper = (ViewFlipper) findViewById(R.id.viewFlipper2);
        m_viewFlipper.setOnTouchListener(this);

        // ViewFlipper에 서브 레이아웃 추가
        RelativeLayout sub1 = (RelativeLayout) View.inflate(this,
        R.layout.subxml1, null);
        RelativeLayout sub2 = (RelativeLayout) View.inflate(this,
        R.layout.subxml2, null);
        m_viewFlipper.addView(sub1);
        m_viewFlipper.addView(sub2);
        m_viewFlipper.refreshDrawableState();
        powerButton = (ImageButton) findViewById(R.id.offBtn);
        powerText =(ImageView) findViewById(R.id.power_text);

        left1 =(ImageView) findViewById(R.id.left_1);
        leftText1 =(ImageView) findViewById(R.id.leftText_1);
        left2 =(ImageView) findViewById(R.id.left_2);
        leftText2 =(ImageView) findViewById(R.id.leftText_2);
        left3 =(ImageView) findViewById(R.id.left_3);
        leftText3 =(ImageView) findViewById(R.id.leftText_3);
        left4 =(ImageView) findViewById(R.id.left_4);
        leftText4 =(ImageView) findViewById(R.id.leftText_4);
        right1 =(ImageView) findViewById(R.id.right_1);
        rightText1 =(ImageView) findViewById(R.id.rightText_1);
        right2 =(ImageView) findViewById(R.id.right_2);
        rightText2 =(ImageView) findViewById(R.id.rightText_2);
        right3 =(ImageView) findViewById(R.id.right_3);
        rightText3 =(ImageView) findViewById(R.id.rightText_3);
        right4 =(ImageView) findViewById(R.id.right_4);
        rightText4 =(ImageView) findViewById(R.id.rightText_4);
        stateLine =(ImageView) findViewById(R.id.state_line);
        totalPer =(ImageView) findViewById(R.id.total_p);



        RSlideImageButton = (ImageView) findViewById(R.id.RSlideImageButton);
        LSlideImageButton = (ImageView) findViewById(R.id.LSlideImageButton);
        RefreshButton = (ImageView) findViewById(R.id.RefreshButton);




        RSlideImageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                hideNext();
                showBefore();
                MoveNextView();
            }
        });

        LSlideImageButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showNext();
                hideBefore();
                MovewPreviousView();
            }
        });

        RefreshButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ConnectWeb();
                InitPage();
            }
        });

        powerButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (checkimg == 1) {
                    powerButton.setImageResource(R.drawable.power_on1);
                    powerText.setImageResource(R.drawable.on);
                    PostOn();
                 //   powerText.setText("On");
                    checkimg = 2;
                } else {
                    powerButton.setImageResource(R.drawable.power_off1);
                 //   powerText.setText("Off");
                    powerText.setImageResource(R.drawable.off);
                    PostOff();
                    checkimg = 1;
                }
            }
        });

        powerButton.setImageResource(R.drawable.power_off1);
        powerText.setImageResource(R.drawable.off);

        ConnectWeb();
        InitPage();
    }

    private void PostOn()
    {
        test = "http://www.recycup.com/PostOn.php" ;
        task = new URLConnector(test);

        task.start();
    }

    private void PostOff()
    {
        test = "http://www.recycup.com/PostOff.php" ;
        task = new URLConnector(test);

        task.start();
    }

    private void ConnectWeb()
    {
        test = "http://www.recycup.com/SelectAllPost.php" ;
        task = new URLConnector(test);

        task.start();

        try
        {
            task.join();
            System.out.println("waiting... for result");
        }
        catch (InterruptedException e)
        {
            System.out.println("error");
        }

        String result = task.getResult();
        System.out.println(result);
        try
        {
            JSONObject root = new JSONObject(result);

            JSONArray ja = root.getJSONArray("result");

            for(int i = 0; i < ja.length(); i++)
            {
                JSONObject jo = ja.getJSONObject(i);
                onoff = jo.getInt("onoff");
                R_1 = jo.getInt("rcup1");
                R_2 = jo.getInt("rcup2");
                R_3 = jo.getInt("rcup3");
                R_4 = jo.getInt("rcup4");
                L_1 = jo.getInt("lcup1");
                L_2 = jo.getInt("lcup2");
                L_3 = jo.getInt("lcup3");
                L_4 = jo.getInt("lcup4");
            }
        }
        catch (JSONException e)
        {
            e.printStackTrace();
        }
    }

    private void InitPage()
    {

            if (onoff == 1) {
                powerButton.setImageResource(R.drawable.power_on1);
                powerText.setImageResource(R.drawable.on);
                checkimg = 2;
            }
            else if(onoff == 2)
            {
                powerButton.setImageResource(R.drawable.power_off1);
                powerText.setImageResource(R.drawable.off);
                checkimg = 1;
            }

        if(R_1 > 10){
            R_1 = 10;
        }
        if(R_2 > 10)
        {
            R_2 = 10;
        }
        if(R_3 > 10)
        {
            R_3 = 10;
        }
        if(R_4 > 10)
        {
            R_4 = 10;
        }

        if(L_1 > 10)
        {
            L_1 = 10;
        }
        if(L_2 > 10)
        {
            L_2 = 10;
        }
        if(L_3 > 10)
        {
            L_3 = 10;
        }
        if(L_4 > 10)
        {
            L_4 = 10;
        }

            sumValue = R_1 + R_2 + R_3 + R_4 + L_1 + L_2 + L_3 + L_4;

            if (sumValue == 0) {
                stateLine.setImageResource(R.drawable.line_0);
                totalPer.setImageResource(R.drawable.t_0);
            } else if (sumValue <= 8) {
                stateLine.setImageResource(R.drawable.line_10);
                totalPer.setImageResource(R.drawable.t_10);
            } else if (sumValue <= 16) {
                stateLine.setImageResource(R.drawable.line_20);
                totalPer.setImageResource(R.drawable.t_20);
            } else if (sumValue <= 24) {
                stateLine.setImageResource(R.drawable.line_30);
                totalPer.setImageResource(R.drawable.t_30);
            } else if (sumValue <= 32) {
                stateLine.setImageResource(R.drawable.line_40);
                totalPer.setImageResource(R.drawable.t_40);
            } else if (sumValue <= 40) {
                stateLine.setImageResource(R.drawable.line_50);
                totalPer.setImageResource(R.drawable.t_50);
            } else if (sumValue <= 48) {
                stateLine.setImageResource(R.drawable.line_60);
                totalPer.setImageResource(R.drawable.t_60);
            } else if (sumValue <= 56) {
                stateLine.setImageResource(R.drawable.line_70);
                totalPer.setImageResource(R.drawable.t_70);
            } else if (sumValue <= 64) {
                stateLine.setImageResource(R.drawable.line_80);
                totalPer.setImageResource(R.drawable.t_80);
            } else if (sumValue <= 72) {
                stateLine.setImageResource(R.drawable.line_90);
                totalPer.setImageResource(R.drawable.t_90);
            } else  {
                stateLine.setImageResource(R.drawable.line_100);
                totalPer.setImageResource(R.drawable.t_100);
            }

            if (R_1 == 0) {
                right1.setImageResource(R.drawable.s_0);
                rightText1.setImageResource(R.drawable.p_0);
            } else if (R_1 <= 1) {
                right1.setImageResource(R.drawable.s_10);
                rightText1.setImageResource(R.drawable.p_10);
            } else if (R_1 <= 2) {
                right1.setImageResource(R.drawable.s_20);
                rightText1.setImageResource(R.drawable.p_20);
            } else if (R_1 <= 3) {
                right1.setImageResource(R.drawable.s_30);
                rightText1.setImageResource(R.drawable.p_30);
            } else if (R_1 <= 4) {
                right1.setImageResource(R.drawable.s_40);
                rightText1.setImageResource(R.drawable.p_40);
            } else if (R_1 <= 5) {
                right1.setImageResource(R.drawable.s_50);
                rightText1.setImageResource(R.drawable.p_50);
            } else if (R_1 <= 6) {
                right1.setImageResource(R.drawable.s_60);
                rightText1.setImageResource(R.drawable.p_60);
            } else if (R_1 <= 7) {
                right1.setImageResource(R.drawable.s_70);
                rightText1.setImageResource(R.drawable.p_70);
            } else if (R_1 <= 8) {
                right1.setImageResource(R.drawable.s_80);
                rightText1.setImageResource(R.drawable.p_80);
            } else if (R_1 <= 9) {
                right1.setImageResource(R.drawable.s_90);
                rightText1.setImageResource(R.drawable.p_90);
            } else {
                right1.setImageResource(R.drawable.s_100);
                rightText1.setImageResource(R.drawable.p_100);
            }


            if (R_2 == 0) {
                right2.setImageResource(R.drawable.s_0);
                rightText2.setImageResource(R.drawable.p_0);
            } else if (R_2 <= 1) {
                right2.setImageResource(R.drawable.s_10);
                rightText2.setImageResource(R.drawable.p_10);
            } else if (R_2 <= 2) {
                right2.setImageResource(R.drawable.s_20);
                rightText2.setImageResource(R.drawable.p_20);
            } else if (R_2 <= 3) {
                right2.setImageResource(R.drawable.s_30);
                rightText2.setImageResource(R.drawable.p_30);
            } else if (R_2 <= 4) {
                right2.setImageResource(R.drawable.s_40);
                rightText2.setImageResource(R.drawable.p_40);
            } else if (R_2 <= 5) {
                right2.setImageResource(R.drawable.s_50);
                rightText2.setImageResource(R.drawable.p_50);
            } else if (R_2 <= 6) {
                right2.setImageResource(R.drawable.s_60);
                rightText2.setImageResource(R.drawable.p_60);
            } else if (R_2 <= 7) {
                right2.setImageResource(R.drawable.s_70);
                rightText2.setImageResource(R.drawable.p_70);
            } else if (R_2 <= 8) {
                right2.setImageResource(R.drawable.s_80);
                rightText2.setImageResource(R.drawable.p_80);
            } else if (R_2 <= 9) {
                right2.setImageResource(R.drawable.s_90);
                rightText2.setImageResource(R.drawable.p_90);
            } else {
                right2.setImageResource(R.drawable.s_100);
                rightText2.setImageResource(R.drawable.p_100);
            }

            if (R_3 == 0) {
                right3.setImageResource(R.drawable.s_0);
                rightText3.setImageResource(R.drawable.p_0);
            } else if (R_3 <= 1) {
                right3.setImageResource(R.drawable.s_10);
                rightText3.setImageResource(R.drawable.p_10);
            } else if (R_3 <= 2) {
                right3.setImageResource(R.drawable.s_20);
                rightText3.setImageResource(R.drawable.p_20);
            } else if (R_3 <= 3) {
                right3.setImageResource(R.drawable.s_30);
                rightText3.setImageResource(R.drawable.p_30);
            } else if (R_3 <= 4) {
                right3.setImageResource(R.drawable.s_40);
                rightText3.setImageResource(R.drawable.p_40);
            } else if (R_3 <= 5) {
                right3.setImageResource(R.drawable.s_50);
                rightText3.setImageResource(R.drawable.p_50);
            } else if (R_3 <= 6) {
                right3.setImageResource(R.drawable.s_60);
                rightText3.setImageResource(R.drawable.p_60);
            } else if (R_3 <= 7) {
                right3.setImageResource(R.drawable.s_70);
                rightText3.setImageResource(R.drawable.p_70);
            } else if (R_3 <= 8) {
                right3.setImageResource(R.drawable.s_80);
                rightText3.setImageResource(R.drawable.p_80);
            } else if (R_3 <= 9) {
                right3.setImageResource(R.drawable.s_90);
                rightText3.setImageResource(R.drawable.p_90);
            } else  {
                right3.setImageResource(R.drawable.s_100);
                rightText3.setImageResource(R.drawable.p_100);
            }

            if (R_4 == 0) {
                right4.setImageResource(R.drawable.s_0);
                rightText4.setImageResource(R.drawable.p_0);
            } else if (R_4 <= 1) {
                right4.setImageResource(R.drawable.s_10);
                rightText4.setImageResource(R.drawable.p_10);
            } else if (R_4 <= 2) {
                right4.setImageResource(R.drawable.s_20);
                rightText4.setImageResource(R.drawable.p_20);
            } else if (R_4 <= 3) {
                right4.setImageResource(R.drawable.s_30);
                rightText4.setImageResource(R.drawable.p_30);
            } else if (R_4 <= 4) {
                right4.setImageResource(R.drawable.s_40);
                rightText4.setImageResource(R.drawable.p_40);
            } else if (R_4 <= 5) {
                right4.setImageResource(R.drawable.s_50);
                rightText4.setImageResource(R.drawable.p_50);
            } else if (R_4 <= 6) {
                right4.setImageResource(R.drawable.s_60);
                rightText4.setImageResource(R.drawable.p_60);
            } else if (R_4 <= 7) {
                right4.setImageResource(R.drawable.s_70);
                rightText4.setImageResource(R.drawable.p_70);
            } else if (R_4 <= 8) {
                right4.setImageResource(R.drawable.s_80);
                rightText4.setImageResource(R.drawable.p_80);
            } else if (R_4 <= 9) {
                right4.setImageResource(R.drawable.s_90);
                rightText4.setImageResource(R.drawable.p_90);
            } else{
                right4.setImageResource(R.drawable.s_100);
                rightText4.setImageResource(R.drawable.p_100);
            }

            if (L_1 == 0) {
                left1.setImageResource(R.drawable.s_0);
                leftText1.setImageResource(R.drawable.p_0);
            } else if (L_1 <= 1) {
                left1.setImageResource(R.drawable.s_10);
                leftText1.setImageResource(R.drawable.p_10);
            } else if (L_1 <= 2) {
                left1.setImageResource(R.drawable.s_20);
                leftText1.setImageResource(R.drawable.p_20);
            } else if (L_1 <= 3) {
                left1.setImageResource(R.drawable.s_30);
                leftText1.setImageResource(R.drawable.p_30);
            } else if (L_1 <= 4) {
                left1.setImageResource(R.drawable.s_40);
                leftText1.setImageResource(R.drawable.p_40);
            } else if (L_1 <= 5) {
                left1.setImageResource(R.drawable.s_50);
                leftText1.setImageResource(R.drawable.p_50);
            } else if (L_1 <= 6) {
                left1.setImageResource(R.drawable.s_60);
                leftText1.setImageResource(R.drawable.p_60);
            } else if (L_1 <= 7) {
                left1.setImageResource(R.drawable.s_70);
                leftText1.setImageResource(R.drawable.p_70);
            } else if (L_1 <= 8) {
                left1.setImageResource(R.drawable.s_80);
                leftText1.setImageResource(R.drawable.p_80);
            } else if (L_1 <= 9) {
                left1.setImageResource(R.drawable.s_90);
                leftText1.setImageResource(R.drawable.p_90);
            } else {
                left1.setImageResource(R.drawable.s_100);
                leftText1.setImageResource(R.drawable.p_100);
            }


            if (L_2 == 0) {
                left2.setImageResource(R.drawable.s_0);
                leftText2.setImageResource(R.drawable.p_0);
            } else if (L_2 <= 1) {
                left2.setImageResource(R.drawable.s_10);
                leftText2.setImageResource(R.drawable.p_10);
            } else if (L_2 <= 2) {
                left2.setImageResource(R.drawable.s_20);
                leftText2.setImageResource(R.drawable.p_20);
            } else if (L_2 <= 3) {
                left2.setImageResource(R.drawable.s_30);
                leftText2.setImageResource(R.drawable.p_30);
            } else if (L_2 <= 4) {
                left2.setImageResource(R.drawable.s_40);
                leftText2.setImageResource(R.drawable.p_40);
            } else if (L_2 <= 5) {
                left2.setImageResource(R.drawable.s_50);
                leftText2.setImageResource(R.drawable.p_50);
            } else if (L_2 <= 6) {
                left2.setImageResource(R.drawable.s_60);
                leftText2.setImageResource(R.drawable.p_60);
            } else if (L_2 <= 7) {
                left2.setImageResource(R.drawable.s_70);
                leftText2.setImageResource(R.drawable.p_70);
            } else if (L_2 <= 8) {
                left2.setImageResource(R.drawable.s_80);
                leftText2.setImageResource(R.drawable.p_80);
            } else if (L_2 <= 9) {
                left2.setImageResource(R.drawable.s_90);
                leftText2.setImageResource(R.drawable.p_90);
            } else {
                left2.setImageResource(R.drawable.s_100);
                leftText2.setImageResource(R.drawable.p_100);
            }

        if (L_3 == 0)
        {
            left3.setImageResource(R.drawable.s_0);
            leftText3.setImageResource(R.drawable.p_0);
        }
        else if (L_3 <= 1)
        {
            left3.setImageResource(R.drawable.s_10);
            leftText3.setImageResource(R.drawable.p_10);
        }
        else if (L_3 <= 2)
        {
            left3.setImageResource(R.drawable.s_20);
            leftText3.setImageResource(R.drawable.p_20);
        }
        else if (L_3 <= 3)
        {
            left3.setImageResource(R.drawable.s_30);
            leftText3.setImageResource(R.drawable.p_30);
        }
        else if (L_3 <= 4)
        {
            left3.setImageResource(R.drawable.s_40);
            leftText3.setImageResource(R.drawable.p_40);
        }
        else if (L_3 <= 5)
        {
            left3.setImageResource(R.drawable.s_50);
            leftText3.setImageResource(R.drawable.p_50);
        }
        else if (L_3 <= 6)
        {
            left3.setImageResource(R.drawable.s_60);
            leftText3.setImageResource(R.drawable.p_60);
        }
        else if (L_3 <= 7)
        {
            left3.setImageResource(R.drawable.s_70);
            leftText3.setImageResource(R.drawable.p_70);
        }
        else if (L_3 <= 8)
        {
            left3.setImageResource(R.drawable.s_80);
            leftText3.setImageResource(R.drawable.p_80);
        }
        else if (L_3 <= 9)
        {
            left3.setImageResource(R.drawable.s_90);
            leftText3.setImageResource(R.drawable.p_90);
        }
        else
        {
            left3.setImageResource(R.drawable.s_100);
            leftText3.setImageResource(R.drawable.p_100);
        }

        if (L_4 == 0)
        {
            left4.setImageResource(R.drawable.s_0);
            leftText4.setImageResource(R.drawable.p_0);
        }
        else if (L_4 <= 1)
        {
            left4.setImageResource(R.drawable.s_10);
            leftText4.setImageResource(R.drawable.p_10);
        }
        else if (L_4 <= 2)
        {
            left4.setImageResource(R.drawable.s_20);
            leftText4.setImageResource(R.drawable.p_20);
        }
        else if (L_4 <= 3)
        {
            left4.setImageResource(R.drawable.s_30);
            leftText4.setImageResource(R.drawable.p_30);
        }
        else if (L_4 <= 4)
        {
            left4.setImageResource(R.drawable.s_40);
            leftText4.setImageResource(R.drawable.p_40);
        }
        else if (L_4 <= 5)
        {
            left4.setImageResource(R.drawable.s_50);
            leftText4.setImageResource(R.drawable.p_50);
        }
        else if (L_4 <= 6)
        {
            left4.setImageResource(R.drawable.s_60);
            leftText4.setImageResource(R.drawable.p_60);
        }
        else if (L_4 <= 7)
        {
            left4.setImageResource(R.drawable.s_70);
            leftText4.setImageResource(R.drawable.p_70);
        }
        else if (L_4 <= 8)
        {
            left4.setImageResource(R.drawable.s_80);
            leftText4.setImageResource(R.drawable.p_80);
        }
        else if (L_4 <= 9)
        {
            left4.setImageResource(R.drawable.s_90);
            leftText4.setImageResource(R.drawable.p_90);
        }
        else
        {
            left4.setImageResource(R.drawable.s_100);
            leftText4.setImageResource(R.drawable.p_100);
        }

    }

    private void MoveNextView() {
        m_viewFlipper.setInAnimation(AnimationUtils.loadAnimation(this,
                R.anim.appear_from_right));
        m_viewFlipper.setOutAnimation(AnimationUtils.loadAnimation(this,
                R.anim.disappear_to_left));
        m_viewFlipper.showNext();
    }

    private void MovewPreviousView() {
        m_viewFlipper.setInAnimation(AnimationUtils.loadAnimation(this,
                R.anim.appear_from_left));
        m_viewFlipper.setOutAnimation(AnimationUtils.loadAnimation(this,
                R.anim.disappear_to_right));
        m_viewFlipper.showPrevious();
    }

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        if (event.getAction() == MotionEvent.ACTION_DOWN) {
            m_nPreTouchPosX = (int) event.getX();
        }

        if (event.getAction() == MotionEvent.ACTION_UP) {
            int nTouchPosX = (int) event.getX();

            if (nTouchPosX < m_nPreTouchPosX) {
                MoveNextView();
            } else if (nTouchPosX > m_nPreTouchPosX) {
                MovewPreviousView();
            }

            m_nPreTouchPosX = nTouchPosX;
        }

        return true;
    }

    public void showNext() {
        RSlideImageButton.setVisibility(View.VISIBLE);
        isNextForceHidden = false;
    }

    /**
     * Hide the next button
     */
    public void hideNext() {
        RSlideImageButton.setVisibility(View.INVISIBLE);
        isNextForceHidden = true;
    }

    /**
     * Show the done button
     */
    public void showBefore() {
        LSlideImageButton.setVisibility(View.VISIBLE);
        isDoneForceHidden = false;
    }

    /**
     * Hide the done button
     */
    public void hideBefore() {
        LSlideImageButton.setVisibility(View.INVISIBLE);
        isDoneForceHidden = true;
    }
}
