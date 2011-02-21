#ifndef _NET_STATISTICS_H_
#define _NET_STATISTICS_H_

#include "netDefs.h"
using namespace std;

class NetStatistics
{
public:
    enum attributes {
        ATTR_RECEIVED_PACKETS = 0,
        ATTR_RECEIVED_FRAMES,
        ATTR_RECEIVED_BYTES,
        ATTR_SENT_PACKETS,
        ATTR_SENT_FRAMES,
        ATTR_SENT_BYTES,
        ATTR_DISCARDED_FRAMES,
        ATTR_DISCARDED_BYTES,
        ATTR_LOST_PACKETS,
        ATTR_REDIRECTED_PACKETS,
        ATTR_REDIRECTED_BYTES,
        ATTR_LAST_TIMESTAMP
    };
    static const int NUM_ATTR = ATTR_LAST_TIMESTAMP + 1;

private:
    vector<int> _stats;

public:
    NetStatistics();

    void setAttr(int name, int value);
    int getAttr(int name, bool clear = false);
    static string getAttrName(int name);
    int clearAttr(int name);
    void increment(int name, int value = 1);
    void zeroAll();
};

class NetStatisticsMonitor : public Runnable
{
private:
    static const int DEFAULT_LOST_THRESHOLD = 10; // 10%
    static const int HISTORY_SIZE = 10; // em s

private:
    NetStatistics* _stats;
    bool _stopThread;

    double _lostThreshold;

public:
    NetStatisticsMonitor()
        : Runnable()
        , _lostThreshold(DEFAULT_LOST_THRESHOLD)
    {
    }

    virtual ~NetStatisticsMonitor()
    {
        setNetStatistics(NULL);
    }

    void threadFunction()
    {
        vector< list<int> > history(_stats->NUM_ATTR);
        vector<int> avg(_stats->NUM_ATTR, 0);

        while (!_stopThread) {
            for (int i = 0; i < _stats->NUM_ATTR; ++i) {
                history.at(i).push_back(_stats->getAttr(i));
                if (history.at(i).size() > HISTORY_SIZE + 1) // + 1 porque para fazer média de 1 segundo deve possuir duas amostras
                    history.at(i).pop_front();
                if (history.at(i).size() > 1)
                    avg.at(i) = (history.at(i).back() - history.at(i).front()) / history.at(i).size();
            }

            int lost = avg.at(NetStatistics::ATTR_LOST_PACKETS),
                rcvd = avg.at(NetStatistics::ATTR_RECEIVED_PACKETS);

            cout << "lost: " << lost << " rcvd: " << rcvd << endl;
            if ((lost*100) / (rcvd+1) > _lostThreshold)
                callback_lostThreshold(lost, rcvd);
            Seconds(1).sleep();
        }
        
    }

    void setNetStatistics(NetStatistics* statistics)
    {
        if (isRunning()) {
            _stopThread = true;
            join();
        }
        _stats = statistics;
        if (_stats) {
            _stopThread = false;
            run(true);
        }
    }

    virtual void callback_lostThreshold(double value, int bitrate)
    {
        LogData log;
        log << "Taxa de perdas: " << value << ", bitrate: " << bitrate / 1000 << "kbps" << endl;
        log.push();
    }

    void setLostThreshold(double threshold) { _lostThreshold = threshold; }
};

#endif

