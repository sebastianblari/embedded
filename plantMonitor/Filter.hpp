#if !defined(FILTER_HPP)
#define FILTER_HPP


#define NO_ERR 0
#define RET_ERR 1


template <typename numType>
class Filter
{
	public:
		Filter();
		~Filter();
		virtual numType getFilteredValue(void);
		numType m_filteredValue;

	private:

};

template<typename numType>
Filter<numType>::Filter()
{

}


template<typename numType>
Filter<numType>::~Filter()
{

}

template<typename numType>
numType Filter<numType>::getFilteredValue(){
    return this->m_filteredValue;
}

#endif /* FILTER_HPP */
